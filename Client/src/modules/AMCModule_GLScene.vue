<!--

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

!-->

<template>
	
	<div v-if="(module.type == 'glscene')" style="width:100%; height:100%; display:block; overflow:hidden;">
		
			<div ref="glDiv" style="width:100%;height:100%;"  v-resize="onResize" />
		
	</div>

</template>

<script>

	import WebGLImpl from "../common/AMCImplementation_WebGL.js"

	export default {
		props: ["Application", "module"],
	  
		components: {
		},
		
		data: () => ({				
			glInstance: null
		}),
		
		methods: {
			    animate: function () {
					requestAnimationFrame(this.animate);
									
					if (this.glInstance)
						this.glInstance.renderScene ();
						
					//const delta = this.glInstance.clock.getDelta();


				},
				
				onResize: function () {
					var domelement = this.$refs.glDiv; 
					if (!domelement) 
						return;	
						
					if (!this.glInstance) 
						return;
						
					this.glInstance.resizeTo (domelement.clientWidth, domelement.clientHeight);
				},
		},
		
		
		created () {
			this.glInstance = this.Application.retrieveWebGLInstance (module.uuid);
			if (!this.glInstance) {
				this.glInstance = new WebGLImpl ();
				this.Application.storeWebGLInstance (this.glInstance);
								
			}
		},
		
		mounted() {
				
			const glDiv = this.$refs.glDiv;
			if (glDiv && this.glInstance) {						
			
				var width = glDiv.clientWidth;
				var height = glDiv.clientHeight;
				if ((width > 0) && (height > 0)) {
					this.glInstance.setupPerspectiveView (45, width / height, 1, 3000);
					this.glInstance.setCameraPosition (150, 150, 150);
					this.glInstance.resizeTo (width, height);
					this.glInstance.setupDOMElement (glDiv);														
					
					
					this.glInstance.addAmbientLight ("ambientlight", 0x808080, 3);

					
					/*this.mesh1 = this.glInstance.addMeshElement ("mesh1", this.Application, "fff71800-4b1d-489e-8679-1f90b9b26646");
					this.mesh1.setPosition (0,0, 0.0, 0.0);

					this.mesh2 = this.glInstance.addMeshElement ("mesh2", this.Application, "e7cf4193-c77d-49b3-b8e3-edf266454a50", 0xc0c0c0);
					this.mesh2.setPosition (0,0, 0.0, 0.0); */
					
					let scene = this.module.scene;
					for (let instance of scene.instances) {
						let mesh = this.glInstance.addMeshElement (instance.instancename, this.Application, instance.meshuuid);
						mesh.setPosition (0,0, 0.0, 0.0);
					
					}
					 
					
					this.glInstance.setupDemoScene ();
					this.animate();
				}
				
			}
		}
		
	};
	
</script>