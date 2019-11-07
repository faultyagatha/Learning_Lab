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

    //robot's head
    let offset = 0.01;
    let headRadius = 0.1;
    let headGeometry = new THREE.SphereBufferGeometry(headRadius, 32, 32); 
    let headMesh = new THREE.Mesh(headGeometry, material);
    headMesh.position.set(0, torsoHeight*0.52+headRadius+offset, 0);
    headMesh.name = 'head';
    torsoMesh.add(headMesh);

    //robot's arms
    let armWidth = 0.1;
    let armHeight = torsoHeight*0.5;
    let armDepth = 0.1;
    let armGeometry = new THREE.BoxBufferGeometry(armWidth, armHeight, armDepth);

    let leftArmMesh = new THREE.Mesh(armGeometry, material);
    leftArmMesh.rotateZ(Math.PI*0.5);
    leftArmMesh.position.set(torsoWidth+offset, torsoHeight*0.5 - armWidth*0.5, 0);
    leftArmMesh.name = 'left arm';
    torsoMesh.add(leftArmMesh);

    let rightArmMesh = leftArmMesh.clone();
    // rightArmMesh.rotateZ(Math.PI*0.5);
    rightArmMesh.position.set(-(torsoWidth+offset), torsoHeight*0.5 - armWidth*0.5, 0);
    rightArmMesh.name = 'right arm';
    torsoMesh.add(rightArmMesh);

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
    rightArmMesh.name = 'right arm';
    torsoMesh.add(rightLegMesh);

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

Robot.prototype.reset = function(){
        this.root.position.set(0., 0., 0.);
        this.root.setRotationFromEuler(new THREE.Euler(0,0,0));
        //restore original colour
        this.root.traverse(function(node) {
            if(node instanceof THREE.Mesh) {
                console.log(node.name);
                node.material = new THREE.MeshLambertMaterial( {
                    color: "blue", 
                    } );
            }
       } );   
};

//this one works but selects all children in one click
Robot.prototype.selectChild = function() {
    this.root.traverse(function(node) {
        console.log(node.name);
        if(node.children[0] instanceof THREE.Mesh) {
            console.log(node.children[0].name);
            let newMaterial = new THREE.MeshLambertMaterial( {
                color: "red", 
                } );
            node.children[0].material = newMaterial;
        }
    });   
} 

Robot.prototype.selectParent = function() { 
    this.root.traverse(function(node) {
        if(node instanceof THREE.Mesh && node.parent) {
            node.parent.material = new THREE.MeshLambertMaterial( {
                color: "red", 
                } );
            console.log(node.name);
        }
    } );
}

// Robot.prototype.selectChild = function(forward) {
//     //I may need the lenths
//     // this.counter = forward.children.length;
//     let firstChild = this.root.children[0];
//     console.log(firstChild.name);
//     if(firstChild instanceof THREE.Mesh) {
//         firstChild.material = new THREE.MeshLambertMaterial( {
//             color: "red",
//         } );
//     } 
// };

// Robot.prototype.selectChild = function(forward) {
//     const firstIndex = forward.children[0];
//     forward.children.forEach((child, index) => {
//         if(index === firstIndex);
//         this.selectChild(child);
//         console.log(child, "is selected");
//     } );
// };

// Robot.prototype.selectChild = function(forward) {
//     //I may need the lenths
//     // this.counter = forward.children.length;
//     let firstChild = forward.children[0];
//     console.log(firstChild.name);
//     if(firstChild instanceof THREE.Mesh) {
//         firstChild.material = new THREE.MeshLambertMaterial( {
//             color: "red",
//         } );
//     } 
// };

Robot.prototype.selectSibling = function(forward) {
    
    let prev = d3.select(this.previousSibling);
    let allChildren = this.root.children;
};

Robot.prototype.toggleSelection = function() {
//here I need to activate reycasting
};

Robot.prototype.selectAll = function() {
    this.root.traverse(function(node) {
        if(node instanceof THREE.Mesh) {
            console.log(node.name);
            node.material = new THREE.MeshLambertMaterial( {
                color: "red", 
                } );
        }
        
    } );   
};

//reference: https://threejs.org/docs/#api/en/math/Quaternion
Robot.prototype.rotateOnAxis = function(axis, degree) {
    let angle = degToRad(degree);
    console.log(angle);
    let quaternion = new THREE.Quaternion();
    quaternion.setFromAxisAngle(axis, angle);
    this.root.applyQuaternion(quaternion);

};

Robot.prototype.animate = function() {
    this.root.getObjectByName('pivot').rotationY += 0.01;
}

