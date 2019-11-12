var Robot = function() {

    this.root = new THREE.Object3D;
    this.root.name = 'robot';
};

Robot.prototype.buildRobot = function() {

    let material = new THREE.MeshLambertMaterial( {
        color: "blue", 
    } );

    /* a lousy attempt to use pivots for rotations that don't work how I want them to work
    */ 
    // let leftLegPivot = new THREE.Object3D();
    // leftLegPivot.name = 'left leg pivot';
    // let rightLegPivot = new THREE.Object3D();
    // rightLegPivot.name = 'right leg pivot';
    // let leftFootPivot = new THREE.Object3D();
    // leftFootPivot.name = 'left foot pivot';
    // let rightFootPivot = new THREE.Object3D();
    // rightFootPivot.name = 'right foot pivot';
    // let leftArmPivot = new THREE.Object3D();
    // leftArmPivot.name = 'left arm pivot';
    // let rightArmPivot = new THREE.Object3D();
    // rightArmPivot.name = 'right arm pivot';
    // let headPivot = new THREE.Object3D();
    // headPivot.name = 'head pivot';

    //robot's torso
    let torsoWidth = 0.2;
    let torsoHeight = 0.35;
    let torsoDepth = 0.2;
    let torsoGeometry = new THREE.BoxBufferGeometry(torsoWidth, torsoHeight, torsoDepth);
    let torsoMesh = new THREE.Mesh(torsoGeometry, material);
    torsoMesh.name = 'torso';
    this.root.add(torsoMesh);

     //robot's legs
     let legWidth = 0.1;
     let legHeight = torsoHeight*0.8;
     let legDepth = 0.1;
     let legGeometry = new THREE.BoxBufferGeometry(legWidth, legHeight, legDepth);
     let leftLegMesh = new THREE.Mesh(legGeometry, material);
     leftLegMesh.position.set(torsoWidth*0.5, torsoHeight*0.5-legHeight*1.9, 0);
     leftLegMesh.name = 'left leg';
     console.log(leftLegMesh.position);
     leftLegMesh.position.set(torsoWidth*0.5, torsoHeight*0.5-legHeight*1.9, 0);
     torsoMesh.add(leftLegMesh);
    //  leftLegPivot.add(leftLegMesh);
    //  leftLegPivot.position.set(0, leftLegMesh.position.y+0.38, 0);
    //  torsoMesh.add(leftLegPivot);
    
     let rightLegMesh = leftLegMesh.clone();
     rightLegMesh.position.set(-torsoWidth*0.5, torsoHeight*0.5-legHeight*1.9, 0);
     rightLegMesh.name = 'right leg';
     rightLegMesh.position.set(-torsoWidth*0.5, torsoHeight*0.5-legHeight*1.9, 0);
     torsoMesh.add(rightLegMesh);
    //  rightLegPivot.add(rightLegMesh);
    //  rightLegPivot.position.set(0, rightLegMesh.position.y+0.38, 0);
    //  torsoMesh.add(rightLegPivot);

    //robot's head
    let offset = 0.01;
    let headRadius = 0.1;
    let headGeometry = new THREE.SphereBufferGeometry(headRadius, 32, 32); 
    let headMesh = new THREE.Mesh(headGeometry, material);
    headMesh.position.set(0, torsoHeight*0.52+headRadius+offset, 0);
    headMesh.name = 'head';
    torsoMesh.add(headMesh);


    //robot's arms
    let armHeight = 0.1;
    let armWidth = torsoHeight*0.5;
    let armDepth = 0.1;
    let armGeometry = new THREE.BoxBufferGeometry(armWidth, armHeight, armDepth);

    let leftArmMesh = new THREE.Mesh(armGeometry, material);
    leftArmMesh.position.set(torsoWidth+offset, torsoHeight*0.5 - armWidth*0.5, 0);
    leftArmMesh.name = 'left arm';
    torsoMesh.add(leftArmMesh);
    // leftArmPivot.position.set(torsoWidth+offset, torsoHeight*0.5 - armWidth*0.5, 0);
    // torsoMesh.add(leftArmPivot);
    // leftArmPivot.add(leftArmMesh);

    let rightArmMesh = leftArmMesh.clone();
    rightArmMesh.position.set(-(torsoWidth+offset), torsoHeight*0.5 - armWidth*0.5, 0);
    torsoMesh.add(rightArmMesh);
    rightArmMesh.name = 'right arm';
    // torsoMesh.add(rightArmPivot);
    // rightArmPivot.position.set(-(torsoWidth+offset), torsoHeight*0.5 - armWidth*0.5, 0);
    // rightArmPivot.add(rightArmMesh);
    

    //robot's feet
    let footWidth = 0.1;
    let footHeight = 0.07;
    let footDepth = 0.15;
    let footGeometry = new THREE.BoxBufferGeometry(footWidth, footHeight, footDepth);
    let leftFootMesh = new THREE.Mesh(footGeometry, material);
    leftFootMesh.position.set(0, leftLegMesh.position.y*0.5-offset, 0);
    leftFootMesh.name = 'left foot';
    leftLegMesh.add(leftFootMesh);

    let rightFootMesh = leftFootMesh.clone();
    rightFootMesh.position.set(0, rightLegMesh.position.y*0.5-offset, 0);
    rightFootMesh.name = 'right foot';
    rightLegMesh.add(rightFootMesh);

    //helpers
    this.outputObjects = function() {
        console.log('this root children: ', this.root.children);
        console.log('this torso children: ', torsoMesh.children);
    }
    this.outputObjects();
    this.numberOfObjects = torsoMesh.children.length;
    console.log(this.numberOfObjects);
    return this.root
};

Robot.prototype.reset = function() {
    this.root.traverse(function(node) {
		// if(node instanceof THREE.Mesh) {
            node.setRotationFromEuler(new THREE.Euler(0,0,0));
        // }
   } );   
        this.resetColour();
};

//restore original colour
Robot.prototype.resetColour = function() {
	this.root.traverse(function(node) {
		if(node instanceof THREE.Mesh) {
			console.log(node.name);
			node.material = new THREE.MeshLambertMaterial( {
				color: "blue", 
			} );
		}
   } );   
}

//works but selects all parents in one click
//gives funny results when rotating with arrows
Robot.prototype.selectParent = function(forward) { 
    forward.traverse(function(node) {
        if(node instanceof THREE.Mesh && node.parent) {
            node.parent.material = new THREE.MeshLambertMaterial( {
                color: "#ff0000", 
                } );
            console.log(node.parent.name);
        }
    } );
}

//selects all children in one click
//gives funny results when rotating with arrows
Robot.prototype.selectChild = function(forward) {
    forward.traverse(function(node) {
        if(node.children[0] instanceof THREE.Mesh && node.children[0].visible) {
            node.children[0].material = new THREE.MeshLambertMaterial( {
                color: "red",
                        } ); 
        }
    } );
}

Robot.prototype.selectSibling = function(forward) {
        for(let i=0; i<forward.children.length; i++) {
            console.log(forward.children.length);
            if(forward.children[i] instanceof THREE.Mesh && forward.children[i].visible) {
                forward.children[i].material = new THREE.MeshLambertMaterial( {
                    color: "red",
                            } ); 
            }
        }
};

//get the selected node
Robot.prototype.toggleSelection = function() {

};

Robot.prototype.selectAll = function() {
    this.root.traverse(function(node) {
        if(node instanceof THREE.Mesh) {
            console.log(node.name, typeof node);
            node.material = new THREE.MeshLambertMaterial( {
                color: "red", 
            } );
        }
    } );   
};

Robot.prototype.rotateOnAxis = function(axis, degree) {
    let angle = degToRad(degree);
    console.log(angle);
    //1. rotate with quaternioun: doen't work as needed
    //reference: https://threejs.org/docs/#api/en/math/Quaternion
    // let quaternion = new THREE.Quaternion();
    // quaternion.setFromAxisAngle(axis, angle);

    //2. rotate with matrices: works but ignoring pivot [see the implementation below]
    //hints: https://gist.github.com/clavis-magna/4138387
    let rotationMatrix = new THREE.Matrix4();
    rotationMatrix.makeRotationAxis(axis, angle);
    // we could also rotate using quaternion: rotationMatrix.makeRotationFromQuaternion(quaternion);

    this.root.traverse(function(node) {
        if(node instanceof THREE.Mesh) {
            if(node.material.color.getStyle() === 'rgb(255,0,0)') {
                // post-multiply matrices to rotate an object around an axis in object space
                rotationMatrix.multiply(node.matrix); 
                // console.log(node.matrix);
                node.matrix = rotationMatrix;
                node.rotation.setFromRotationMatrix(node.matrix,'XYZ');
                // node.applyQuaternion(quaternion);
            } 
        }
    } );
};

//this one rotates more or less accurate (or as it seems :)) but only once
// Robot.prototype.rotateOnAxis = function(axis, degree) {
//     let angle = degToRad(degree);
//     console.log(angle);

//     //local rotation matrix
//     let rotationMatrix = new THREE.Matrix4(); 

//     this.root.traverse(function(node) {
//         if(node instanceof THREE.Mesh) {
//             if(node.material.color.getStyle() === 'rgb(255,0,0)') {
//                 // post-multiply matrices 
//                 rotationMatrix.makeRotationAxis(axis, angle);
//                 node.parent.matrix.multiply(rotationMatrix);                       // post-multiply
//                 node.parent.matrix = rotationMatrix;
//                 node.parent.rotation.setFromRotationMatrix(node.parent.matrix,'XYZ');
//             }
//         }
//     } );
// };


Robot.prototype.animate = function() {
    
}

