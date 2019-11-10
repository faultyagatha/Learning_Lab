var Robot = function() {

    this.root = new THREE.Object3D;
    this.root.name = 'robot';
};

/*we can add a property to a previously defined object type by using the prototype property. 
This defines a property that is shared by all objects of the specified type, 
rather than by just one instance of the object. 
*/
Robot.prototype.buildRobot = function() {

    let material = new THREE.MeshLambertMaterial( {
        color: "blue",  // CSS color names can be used!
    } );

    //pivot
    // let pivot = new THREE.Group();
    // pivot.position.set(0., 0., 0.);
    // pivot.name = 'pivot';

    //robot's torso
    let torsoWidth = 0.2;
    let torsoHeight = 0.35;
    let torsoDepth = 0.2;
    let torsoGeometry = new THREE.BoxBufferGeometry(torsoWidth, torsoHeight, torsoDepth);
    let torsoMesh = new THREE.Mesh(torsoGeometry, material);
    torsoMesh.name = 'torso';
    this.root.add(torsoMesh);
    // this.root.add(pivot);
    // pivot.add(torsoMesh);

     //robot's legs
     let legWidth = 0.1;
     let legHeight = torsoHeight*0.8;
     let legDepth = 0.1;
     let legGeometry = new THREE.BoxBufferGeometry(legWidth, legHeight, legDepth);
     let leftLegMesh = new THREE.Mesh(legGeometry, material);
     leftLegMesh.position.set(torsoWidth*0.5, torsoHeight*0.5-legHeight*1.9, 0);
     leftLegMesh.name = 'left leg';
     torsoMesh.add(leftLegMesh);
 
     let rightLegMesh = leftLegMesh.clone();
     rightLegMesh.position.set(-torsoWidth*0.5, torsoHeight*0.5-legHeight*1.9, 0);
     rightLegMesh.name = 'right leg';
     torsoMesh.add(rightLegMesh);

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

    let rightArmMesh = leftArmMesh.clone();
    rightArmMesh.position.set(-(torsoWidth+offset), torsoHeight*0.5 - armWidth*0.5, 0);
    rightArmMesh.name = 'right arm';
    torsoMesh.add(rightArmMesh);

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
		if(node instanceof THREE.Mesh) {
            node.setRotationFromEuler(new THREE.Euler(0,0,0));
        }
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
//gives funny results when rotating with arrows :)
Robot.prototype.selectParent = function() { 
    this.root.traverse(function(node) {
        if(node instanceof THREE.Mesh && node.parent) {
            node.parent.material = new THREE.MeshLambertMaterial( {
                color: "#ff0000", 
                } );
            console.log(node.parent.name);
            // return node.parent;
        }
    } );
}

//works but selects all children in one click
//gives funny results when rotating with arrows :)
Robot.prototype.selectChild = function(forward) {
    forward.traverse(function(node) {
        if(node.children[0] instanceof THREE.Mesh) {
            node.children[0].material = new THREE.MeshLambertMaterial( {
                color: "red",
                        } ); 
            // forward = forward.children[0];
        }
    } );
}


Robot.prototype.selectSibling = function(node) {
    if(!node) {
        console.log('node is undefined');
        return this;
    }
        let firstChild = node.children[0];
        console.log(firstChild);
        while(firstChild.node) {
            firstChild = firstChild.children;
            console.log('first child is ', firstChild);
            return firstChild.mesh;
        }
};

//get the selected node
Robot.prototype.toggleSelection = function() {

};

// Robot.prototype.toggleSelection = function() {
//     // let node = this.root.children[0];
//     this.root.traverse(function(node) {
//             if(node instanceof THREE.Mesh) {
//                 if(node.material.color.getStyle() === 'rgb(255,0,0)') {
//                     console.log('type is ', typeof node);
//                     console.log('name is ', node.name);
//                     console.log('material is ', node.material.color);
//                     // return node;
//                 } 
//         }
//         return this.root;
//     } );

//     // console.log("this object is ", node);
//     // console.log(typeof node);
//     return this.root;
// };

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

    //2. rotate with matrices
    //hints: https://gist.github.com/clavis-magna/4138387
    let rotWorldMatrix = new THREE.Matrix4();
    rotWorldMatrix.makeRotationAxis(axis, angle);

    this.root.traverse(function(node) {
        if(node instanceof THREE.Mesh) {
            if(node.material.color.getStyle() === 'rgb(255,0,0)') {
            
                // post-multiply matrices
                rotWorldMatrix.multiply(node.matrix); 
                // console.log(node.matrix);
                node.matrix = rotWorldMatrix;
                node.rotation.setFromRotationMatrix(node.matrix,'XYZ');
                // node.applyQuaternion(quaternion);
            } 
        }
    } );
};

Robot.prototype.animate = function() {
    this.root.getObjectByName('pivot').rotationY += 0.01;
}

