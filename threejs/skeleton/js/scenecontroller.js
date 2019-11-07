var SceneController = function(document)
{
    this.scene = new THREE.Scene();
    this.renderer = new THREE.WebGLRenderer( {
        antialias: true,  // to enable anti-alias and get smoother output
        preserveDrawingBuffer: true  // to allow screenshot
    } );
};

SceneController.prototype.setup = function()
{
    // https://threejs.org/docs/#api/renderers/WebGLRenderer
    this.renderer.setSize( window.innerWidth, window.innerHeight);
    document.body.appendChild( this.renderer.domElement );

    this.setupCamera();
    this.setupControls();
    this.setupRaycaster();
    this.setupLight();
    this.setupGeometry();

    this.render();
    this.animate();
};

SceneController.prototype.setupCamera = function()
{
    var VIEW_ANGLE = 70;
    var ASPECT_RATIO = window.innerWidth / window.innerHeight;
    var NEAR_PLANE = 0.01;
    var FAR_PLANE = 10;

    // https://threejs.org/docs/#api/cameras/PerspectiveCamera
    this.camera = new THREE.PerspectiveCamera( VIEW_ANGLE, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE );
    this.camera.position.z = 1;
    this.camera.lookAt(this.scene.position);
};

SceneController.prototype.setupControls = function()
{
    // https://threejs.org/examples/misc_controls_orbit.html
    this.controls = new THREE.OrbitControls( this.camera );
    this.controls.enableDamping = true;
    this.controls.enableZoom = true;
    this.controls.enableKeys = false;
    //bind? --> https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/bind
    this.controls.addEventListener( 'change', this.render.bind(this) );
};

SceneController.prototype.setupRaycaster = function() 
{
    this.raycaster = new THREE.Raycaster();
    this.mouse = new THREE.Vector2();

};

SceneController.prototype.raycast = function() {
    this.raycaster.setFromCamera(this.mouse, this.camera);
    let intersects = this.raycaster.intersectObjects(this.robot.root.children);
    console.log('the length of intersection is ', intersects.length);
    if (intersects.length > 0) {
        console.log(intersects.length);
        console.log(intersects[0].object.name);
        intersects[0].object.material = new THREE.MeshLambertMaterial( {
            color: "red", 
        } );

    //     for(let i=0; i<intersects.length; i++) {
    //         console.log(intersects.length);
    //         console.log(intersects[i].object.name);
    //         intersects[i].object.material = new THREE.MeshLambertMaterial( {
    //         color: "red", 
    //     } );
    }
    console.log('picking');
}

SceneController.prototype.setupGeometry = function()
{
    this.robot = new Robot();
    this.scene.add(this.robot.buildRobot());
     //log out the the scene graph to the console
    console.log(this.dumpObject(this.scene).join('\n'));
};

SceneController.prototype.setupLight = function()
{
    var light = new THREE.PointLight( 0xffffcc, 1, 100 );
    light.position.set( 10, 30, 15 );
    this.scene.add(light);

    var light2 = new THREE.PointLight( 0xffffcc, 1, 100 );
    light2.position.set( 10, -30, -15 );
    this.scene.add(light2);

    this.scene.add( new THREE.AmbientLight(0x999999) );
};

SceneController.prototype.render = function() {
    this.renderer.render( this.scene, this.camera );
};

SceneController.prototype.animate = function()
{   
    //bind? --> https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/bind
    requestAnimationFrame( this.animate.bind(this) );
    
    this.controls.update();
};

SceneController.prototype.reset = function()
{
    this.robot.reset();
};

SceneController.prototype.selectParent = function() 
{
    this.robot.selectParent();
};

SceneController.prototype.selectSibling = function(forward)
{
    this.robot.selectSibling(forward);
};

SceneController.prototype.selectChild = function()
{
    this.robot.selectChild();
};

SceneController.prototype.toggleSelection = function()
{
    this.robot.toggleSelection();
};

SceneController.prototype.selectAll = function() {
    this.robot.selectAll();
};

SceneController.prototype.toggleAxisVisibility = function ()
{
    // utils provides two helper functions which could be used
    let axes = buildAxes(10);
    this.scene.add(axes);
    // toggleVisibility(axes); 

};

SceneController.prototype.rotateNode = function(axis, degree)
{
    this.robot.rotateOnAxis(axis, degree);
};

SceneController.prototype.handleMouseClick = function(mouse)
{
    // Reference http://stemkoski.github.io/Three.js/Mouse-Click.html
};

SceneController.prototype.handleMouseMove = function(offsetX, offsetY)
{
};

//dump put the scenegraph to the JavaScript console
//Reference: https://threejsfundamentals.org/threejs/lessons/threejs-load-gltf.html
SceneController.prototype.dumpObject = function(obj, lines = [], isLast = true, prefix = '') {
    const localPrefix = isLast ? '└─' : '├─';
    lines.push(`${prefix}${prefix ? localPrefix : ''}${obj.name || '*no-name*'} [${obj.type}]`);
    const newPrefix = prefix + (isLast ? '  ' : '│ ');
    const lastNdx = obj.children.length - 1;
    obj.children.forEach((child, ndx) => {
      const isLast = ndx === lastNdx;
      this.dumpObject(child, lines, isLast, newPrefix);
    });
    return lines;
  };
