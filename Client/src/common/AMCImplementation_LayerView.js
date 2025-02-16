/*++

Copyright (C) 2020 Autodesk Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
 * Neither the name of the Autodesk Inc. nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AUTODESK INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

const LAYERVIEW_MINSCALING = 0.4;
const LAYERVIEW_MAXSCALING = 4000.0;
const LAYERVIEW_MINVELOCITYRANGE = 1.0;

class LayerViewImpl {

    constructor(glInstance) {

        this.glInstance = glInstance;

        this.currentSize = {
            gridWidth: 0,
            gridHeight: 0,
            viewPortWidth: 0,
            viewPortHeight: 0
        }
        this.transform = {
            x: 0,
            y: 0,
            scaling: 1.0
        }
        this.origin = {
            x: 0,
            y: 0
        }
		
		this.lineScaleLevel = 0;
		this.renderNeedsUpdate = true;

		this.layerSegmentsArray = null;
		
		this.layerPointsMode = "unicolor";
		this.layerPointsArray = null;
		this.layerPointsColorArray = null;
		this.layerPointsVelocities = [];
		this.layerPointsMaxVelocity = LAYERVIEW_MINVELOCITYRANGE;
		this.layerPointsMinVelocity = LAYERVIEW_MINVELOCITYRANGE;
		
        this.linesCoordinates = [];
		
		this.toolpathVisible = true;
		this.pointsVisible = true;
        
		this.updateTransform ();

    }

    updateSize(width, height) {
        if ((width > 0) && (height > 0)) {

            this.currentSize.viewPortWidth = width;
            this.currentSize.viewPortHeight = height;

            if (this.glInstance) {
                this.glInstance.resizeTo(width, height);
                this.glInstance.setup2DView(width, height, 0.1, 100);
            }

            var newWidth = width * 2 + 50;
            var newHeight = height * 2 + 50;

            if ((this.currentSize.gridWidth < newWidth) || (this.currentSize.gridHeight < newHeight)) {
                this.currentSize.gridWidth = newWidth;
                this.currentSize.gridHeight = newHeight;

                this.createGrid(newWidth, newHeight);

            }

        }

		this.renderNeedsUpdate = true;
    }

    createGrid(width, height) {
        if (!this.glInstance)
            return;

        var gridObject = this.glInstance.scene.getObjectByName("grid");
        if (gridObject)
            this.glInstance.scene.remove(gridObject);

        this.glInstance.add2DGridGeometry("grid", width, height, 50, 5);
		this.updateTransform ();
		
		this.renderNeedsUpdate = true;
		

    }

    updateTransform() {

        if (!this.glInstance)
            return;

        var gridgeometry = this.glInstance.findElement("grid");
        if (gridgeometry) {
            var gridScale = this.transform.scaling;
			var lineScaleLevel = 1;

            if (gridScale < 0.5) {
                gridScale = gridScale * 5.0;
				lineScaleLevel = 0.8;
            }

            if (gridScale > 2.5) {
                gridScale = gridScale / 5.0;
				lineScaleLevel = 0.4;
            }

            if (gridScale > 2.5) {
                gridScale = gridScale / 5.0;
				lineScaleLevel = 0.25;
            }

            if (gridScale > 2.5) {
                gridScale = gridScale / 5.0;
				lineScaleLevel = 0.125;
            }

            if (gridScale > 2.5) {
                gridScale = gridScale / 5.0;
				lineScaleLevel = 0.06;
            }

            if (gridScale > 2.5) {
                gridScale = gridScale / 5.0;
				lineScaleLevel = 0.02;
            }
						
            if (gridScale > 2.5) {
                gridScale = gridScale / 5.0;
				lineScaleLevel = 0.01;
            }
			
			console.log ("line scale level: " + lineScaleLevel);
			this.updateLineScaleLevel (lineScaleLevel);

            var fullGridSize = gridScale * 25.0 * 5;
            var gridTranslationX = this.transform.x - Math.ceil((this.transform.x / fullGridSize)) * fullGridSize;
            var gridTranslationY = this.transform.y - Math.ceil((this.transform.y / fullGridSize)) * fullGridSize;

            gridgeometry.setPositionXY(gridTranslationX, gridTranslationY);
            gridgeometry.setScaleXY(gridScale, gridScale);
        }

        var layerlinesgeometry = this.glInstance.findElement("layerdata_lines");
        if (layerlinesgeometry) {
            layerlinesgeometry.setPositionXY(this.transform.x + this.origin.x * this.transform.scaling, this.transform.y - this.origin.y  * this.transform.scaling);
            layerlinesgeometry.setScaleXY(this.transform.scaling,  - this.transform.scaling);
        }

        var layerpointsgeometry = this.glInstance.findElement("layerdata_points");
        if (layerpointsgeometry) {
            layerpointsgeometry.setPositionXY(this.transform.x + this.origin.x * this.transform.scaling, this.transform.y - this.origin.y  * this.transform.scaling);
            layerpointsgeometry.setScaleXY(this.transform.scaling,  - this.transform.scaling);
        } 

        var buildplategeometry = this.glInstance.findElement("buildplate");
        if (buildplategeometry) {
            buildplategeometry.setPositionXY(this.transform.x, this.transform.y, buildplategeometry);
            buildplategeometry.setScaleXY(this.transform.scaling,  - this.transform.scaling);
        }
		
		this.renderNeedsUpdate = true;
    }
	
	updateLineScaleLevel (newLineScaleLevel)
	{
		if (newLineScaleLevel != this.lineScaleLevel) {
			
			this.lineScaleLevel = newLineScaleLevel;
			
			this.updateLoadedLayer ();
			this.updateLayerPoints ();

			this.updateTransform();
			this.RenderScene(true);		
			
			
		}
	}
	
	
	



	getPathBoundaries() {
		let layerLines = this.glInstance.findElement("layerdata_lines");
		if (layerLines) {
			const pathBoundaries = layerLines.glelement.geometry.boundingSphere;

			return pathBoundaries;
		} else {
			return null;
		}
	}


    loadLayer(segmentsArray) {
		this.layerSegmentsArray = segmentsArray;
		this.updateLoadedLayer ();

		this.updateTransform();
		this.RenderScene(true);		
		
	}
	
	computeVelocities ()
	{
		if (this.layerPointsArray) {
			let pointCount = this.layerPointsArray.length / 2;
			
			if (pointCount > 0) {
				let velocities = [];
				let maxVelocity = LAYERVIEW_MINVELOCITYRANGE;
				let minVelocity = LAYERVIEW_MINVELOCITYRANGE;
				
				for (let pointIndex = 0; pointIndex < pointCount; pointIndex++) {
					let velocity = this.getPointVelocity (pointIndex);					
					if (velocity > 0.0) {						
						if (velocity > LAYERVIEW_MINVELOCITYRANGE) {

							if (maxVelocity < velocity)
								maxVelocity = velocity;
							
							if (minVelocity < LAYERVIEW_MINVELOCITYRANGE) {
								minVelocity = velocity;
							}
							if (minVelocity > velocity) {
								minVelocity = velocity;							
							}
							
						}
													
						velocities.push (velocity);									
					} else {
						velocities.push (0.0);
					}
					

				}
				
				if (maxVelocity < LAYERVIEW_MINVELOCITYRANGE)
					maxVelocity = LAYERVIEW_MINVELOCITYRANGE;
				if (minVelocity < LAYERVIEW_MINVELOCITYRANGE)
					minVelocity = LAYERVIEW_MINVELOCITYRANGE;
				
				this.layerPointsVelocities = velocities;
				this.layerPointsMaxVelocity = maxVelocity;
				this.layerPointsMinVelocity = minVelocity;
			
			}
			
			
		} else {
			this.layerPointsVelocities = null;
			this.layerPointsMaxVelocity = LAYERVIEW_MINVELOCITYRANGE;
		}
	}
	
	makeVelocityColors ()
	{
		this.layerPointsColorArray = null;

		if (this.layerPointsVelocities && this.layerPointsArray) {

			const velocityRange = (this.layerPointsMaxVelocity - this.layerPointsMinVelocity);
			if (velocityRange > LAYERVIEW_MINVELOCITYRANGE) {

				let pointCount = this.layerPointsArray.length / 2;
				let colors = [];
				
				for (let pointIndex = 0; pointIndex < pointCount; pointIndex++) {
					let velocity = this.layerPointsVelocities[pointIndex];
					let fraction = (velocity - this.layerPointsMinVelocity) / velocityRange;
					if (fraction >= 0.0) {
						if (fraction > 1.0)
							fraction = 1.0;
					} else {
						fraction = 0.0;
					}
					
					const hue = (1 - fraction) * 240 / 360;
					
					colors.push (this.hslToRgb (hue, 1.0, 0.5));				
					
				}
				
				this.layerPointsColorArray = colors;
			}

		}

	}
	
	hslToRgb(h, s, l) {
		// Ensure h, s, l are in the range [0, 1]
		h = h % 1; // Wrap around if h is greater than 1
		s = Math.min(Math.max(s, 0), 1);
		l = Math.min(Math.max(l, 0), 1);

		if (s === 0) {
			// Achromatic (gray)
			const value = Math.round(l * 255);
			return [value, value, value];
		}

		const hueToRgb = (p, q, t) => {
			if (t < 0) t += 1;
			if (t > 1) t -= 1;
			if (t < 1 / 6) return p + (q - p) * 6 * t;
			if (t < 1 / 2) return q;
			if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
			return p;
		};

		const q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		const p = 2 * l - q;

		const r = hueToRgb(p, q, h + 1 / 3);
		const g = hueToRgb(p, q, h);
		const b = hueToRgb(p, q, h - 1 / 3);

		return Math.round(r * 255) + Math.round(g * 255) * 256 + Math.round(b * 255) * 65536;
			
	}


	makeTimeColors ()
	{
		this.layerPointsColorArray = null;

		if (this.layerPointsVelocities && this.layerPointsArray) {

			let pointCount = this.layerPointsArray.length / 2;
			let colors = [];
			
			for (let pointIndex = 0; pointIndex < pointCount; pointIndex++) {

				let t = pointIndex / pointCount;
				
				const hue = (1 - t) * 240 / 360;
				
				colors.push (this.hslToRgb (hue, 1.0, 0.5));				
				
			}
			
			this.layerPointsColorArray = colors;

		}

	}

	
    loadPoints(pointsArray) {
		this.layerPointsArray = pointsArray;
		this.layerPointsColorArray = null;
		this.layerPointsVelocities = null;
		this.layerPointsMaxVelocity = LAYERVIEW_MINVELOCITYRANGE;
		
		this.computeVelocities ();		
		this.updateColors ();			
		this.updateLayerPoints ();		
	}
	
	updateColors ()
	{
		this.layerPointsColorArray = null;

		if (this.layerPointsMode == "time") {
			this.makeTimeColors ();
		} 

		if (this.layerPointsMode == "velocity") {
			this.makeVelocityColors ();
		} 

	}
	
	setColorMode (newColorMode) {
		this.layerPointsMode = newColorMode;
		this.updateColors ();
		this.updateLayerPoints ();
		this.updateTransform();
		this.RenderScene(true);		
	}
	
	pointDataIsAvailable ()
	{
		if (this.layerPointsArray) {
			return true;
		}
		
		return false;
	}
	
	updateLayerPoints () {
		if (!this.glInstance) 
			return;

		this.glInstance.removeElement("layerdata_points");
						
		if (this.layerPointsArray && this.pointsVisible) {
			this.glInstance.add2DLocalizedPointsGeometry("layerdata_points", this.layerPointsArray, 61, this.lineScaleLevel * 0.06, 0x00d0ff, this.layerPointsColorArray, -200, -200, 2, 2, 400, 400);
			this.updateTransform ();
			this.RenderScene (true);
		}
	}
		
	getPointPosition (pointIndex)
	{
		if (this.layerPointsArray) {
			if (pointIndex >= 0) {
				let arrayIndex = pointIndex * 2;
				if (arrayIndex + 1 < this.layerPointsArray.length) {
					let xPosition = this.layerPointsArray[arrayIndex];
					let yPosition = this.layerPointsArray[arrayIndex + 1];
					return { x: xPosition, y: yPosition }
				}
			}

		}
		
		return null;
					
	}

	getPointVelocity (pointIndex)
	{
		let dT = 1 / 100000;
		
		if (this.layerPointsArray) {
			if (pointIndex > 0) {
				let arrayIndex = pointIndex * 2;
				if (arrayIndex + 3 < this.layerPointsArray.length) {
					let vX = (this.layerPointsArray[arrayIndex + 2] - this.layerPointsArray[arrayIndex - 2]) / (2 * dT);
					let vY = (this.layerPointsArray[arrayIndex + 3] - this.layerPointsArray[arrayIndex - 1]) / (2 * dT);
					let velocity = Math.sqrt (vX * vX + vY * vY);
					return velocity;
				}
			}

		}
		
		return 0.0;
					
	}

	getPointAcceleration (pointIndex)
	{
		let dT = 1 / 100000; 
		
		if (this.layerPointsArray) {
			if (pointIndex > 0) {
				let arrayIndex = pointIndex * 2;
				if (arrayIndex + 3 < this.layerPointsArray.length) {
					let aX = (this.layerPointsArray[arrayIndex + 2] - 2 * this.layerPointsArray[arrayIndex] + this.layerPointsArray[arrayIndex - 2]) / (dT * dT);
					let aY = (this.layerPointsArray[arrayIndex + 3] - 2 * this.layerPointsArray[arrayIndex + 1] + this.layerPointsArray[arrayIndex - 1]) / (dT * dT);
					let accel = Math.sqrt (aX * aX + aY * aY);
					return { ax: aX,  ay: aY, a: accel }
				}
			}

		} 
		
		return null;
					
	}


	getPointJerk (pointIndex)
	{
		let dT = 1 / 100000;
		
		if (this.layerPointsArray) {
			if (pointIndex > 1) {
				let arrayIndex = pointIndex * 2;
				if (arrayIndex + 5 < this.layerPointsArray.length) {
					let aXPrev = (this.layerPointsArray[arrayIndex] - 2 * this.layerPointsArray[arrayIndex - 2] + this.layerPointsArray[arrayIndex - 4]) / (dT * dT);
					let aYPrev = (this.layerPointsArray[arrayIndex + 1] - 2 * this.layerPointsArray[arrayIndex - 1] + this.layerPointsArray[arrayIndex - 3]) / (dT * dT);
					let aXNext = (this.layerPointsArray[arrayIndex + 2] - 2 * this.layerPointsArray[arrayIndex] + this.layerPointsArray[arrayIndex - 2]) / (dT * dT);
					let aYNext = (this.layerPointsArray[arrayIndex + 3] - 2 * this.layerPointsArray[arrayIndex + 1] + this.layerPointsArray[arrayIndex - 1]) / (dT * dT);
					let jX = (aXNext - aXPrev) / (2 * dT);
					let jY = (aYNext - aYPrev) / (2 * dT);
					let jerk = Math.sqrt (jX * jX + jY * jY);
					return { jx: jX,  jy: jY, j: jerk }
				}
			}

		}
		
		return null;
					
	}

	updateLoadedLayer () {
		if (!this.glInstance) 
			return;
		
        this.glInstance.removeElement("layerdata_lines");
		
		if (this.layerSegmentsArray && this.toolpathVisible) {
				
			let segmentsArray = this.layerSegmentsArray;
			var segmentCount = segmentsArray.length;
			var segmentIndex;
			
			this.linesCoordinates = [];
			this.segmentProperties = [];
			
			let vertexcolors = [];

			for (segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++) {
				var segment = segmentsArray[segmentIndex];
				let segmentColor = segment.color;		
				let segmentData = { laserpower: segment.laserpower, laserspeed: segment.laserspeed, profilename: segment.profilename  }

				if ((segment.type === "loop") || (segment.type === "polyline")) {
					var pointCount = segment.points.length;
					var pointIndex;
					
					var oldx = segment.points[0].x;
					var oldy = segment.points[0].y;

					for (pointIndex = 1; pointIndex < pointCount; pointIndex++) {
						var x = segment.points[pointIndex].x;
						var y = segment.points[pointIndex].y;

						this.linesCoordinates.push(oldx, oldy, x, y);
						this.segmentProperties.push (segmentData);
						vertexcolors.push (segmentColor);

						oldx = x;
						oldy = y;
					}
				}

				if (segment.type === "hatch") {
					var lineCount = segment.points.length / 2;
					var lineIndex;

					for (lineIndex = 0; lineIndex < lineCount; lineIndex++) {
						var x1 = segment.points[lineIndex * 2].x;
						var y1 = segment.points[lineIndex * 2].y;
						var x2 = segment.points[lineIndex * 2 + 1].x;
						var y2 = segment.points[lineIndex * 2 + 1].y;

						this.linesCoordinates.push(x1, y1, x2, y2);
						this.segmentProperties.push (segmentData);
						vertexcolors.push (segmentColor);
					}

				}
			}
			
			var layerLinesObject = this.glInstance.scene.getObjectByName("layerdata_lines");
			if (layerLinesObject)
				this.glInstance.scene.remove(layerLinesObject);
			
			
			let thickness = this.lineScaleLevel * 0.3;
			
			console.log ("rebulding layer preview with thickness: " + thickness);
			
			this.glInstance.add2DLineGeometry("layerdata_lines", this.linesCoordinates, 60, thickness, 0x000000, vertexcolors);
		}

		this.updateTransform();
		this.RenderScene(true);		

    }

    Drag(deltaX, deltaY) {

        // console.log("dX: " + deltaX + " dY: " + deltaY);

        this.transform.x = this.transform.x + deltaX;
        this.transform.y = this.transform.y + deltaY;

        this.updateTransform();

    }

    SetAbsoluteScaling(newScaling, centerx, centery) {

        if (!centerx) {
            centerx = this.twoinstance.width * 0.5;
        }

        if (!centery) {
            centery = this.twoinstance.height * 0.5;
        }

        this.ScaleRelative(newScaling / this.transform.scaling, centerx, centery);

    }

    ScaleRelative(factor, centerx, centery) {

        if (!centerx) {
            centerx = this.currentSize.viewPortWidth * 0.5;
        }

        if (!centery) {
            centery = this.currentSize.viewPortHeight * 0.5;
        }

        this.transform.x = this.transform.x - centerx;
        this.transform.y = this.transform.y - centery;

		// console.log("oldscaling: " + this.transform.scaling);

        var oldScaling = this.transform.scaling;
        this.transform.scaling = oldScaling * factor;
        if (this.transform.scaling < LAYERVIEW_MINSCALING)
            this.transform.scaling = LAYERVIEW_MINSCALING;

        if (this.transform.scaling > LAYERVIEW_MAXSCALING)
            this.transform.scaling = LAYERVIEW_MAXSCALING;

		// console.log("newscaling: " + this.transform.scaling);

        factor = this.transform.scaling / oldScaling;

        this.transform.x = Math.ceil(this.transform.x * factor + centerx);
        this.transform.y = Math.ceil(this.transform.y * factor + centery);

        this.updateTransform();
		
    }
	
	CenterOnRectangle (minx, miny, maxx, maxy)
	{
		var sizex = maxx - minx;
		var sizey = maxy - miny;
		
		if ((this.currentSize.viewPortWidth > 0) && (this.currentSize.viewPortHeight > 0)) {
			if ((sizex > 0) && (sizey > 0)) {
				
				var scalingx = (this.currentSize.viewPortWidth / sizex);
				var scalingy = (this.currentSize.viewPortHeight / sizey);
				
				var newcenterx = (maxx + minx) * 0.5;
				var newcentery = (maxy + miny) * 0.5;
				
				var viewcenterx = this.currentSize.viewPortWidth * 0.5;
				var viewcentery = this.currentSize.viewPortHeight * 0.5;
								
				this.transform.x = viewcenterx - this.transform.scaling * newcenterx;
				this.transform.y = viewcentery + this.transform.scaling * newcentery;
								
				var newScaling;
				if (scalingx > scalingy) {
					newScaling = scalingy;
				} else {
					newScaling = scalingx;
				}
				
				this.SetAbsoluteScaling (newScaling, viewcenterx, viewcentery);
			
			}
		}
		
		
	}
	
    RenderScene (forceRender = false) 
	{
		if (forceRender) {
			this.renderNeedsUpdate = true;
		}
		
		if (this.renderNeedsUpdate && this.glInstance) {
			this.glInstance.renderScene ();
			this.renderNeedsUpdate = false;
		}			
		
	} 
	
	SetBuildPlateSVG (url) {
		if (this.glInstance) {
			if (url) {
				this.svgImage = this.glInstance.addSVGImage("buildplate", url, 35, true, true);
			} else {
				this.glInstance.removeElement ("buildplate");
			}
		}
	} 
		
	setOrigin (x, y)
	{
		if (isNaN (x) || isNaN (y))
			return;
		
		this.origin.x = x;
		this.origin.y = y;
	}
}



export default LayerViewImpl;
