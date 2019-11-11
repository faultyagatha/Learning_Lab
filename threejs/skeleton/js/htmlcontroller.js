var HtmlController = function(sceneController)
{
    this.sceneController = sceneController;
    // this.mouseStart = new THREE.Vector2();
    this.lastMousePosition = {};
    this.node = this.sceneController.robot.root;
};

HtmlController.prototype.setup = function()
{
    //bind? --> https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/bind
    window.addEventListener( 'resize', this.onWindowResize.bind(this), false );

    document.addEventListener("keydown", this.onDocumentKeyDown.bind(this), false);
    document.addEventListener("mousedown", this.onDocumentMouseDown.bind(this), false);
    document.addEventListener("mousemove", this.onDocumentMouseMove.bind(this), false);
    document.addEventListener("mouseup", this.onDocumentMouseUp.bind(this), false);
};

//event handler that is called when the window is resized
HtmlController.prototype.onWindowResize = function()
{
    this.sceneController.camera.aspect = window.innerWidth / window.innerHeight;
    this.sceneController.camera.updateProjectionMatrix();

    this.sceneController.renderer.setSize( window.innerWidth, window.innerHeight);
    this.sceneController.render();
};

HtmlController.prototype.onDocumentMouseDown = function(event)
{ 
    this.sceneController.mouse.x = (event.clientX / window.innerWidth) * 2 - 1;
    this.sceneController.mouse.y = - (event.clientY / window.innerHeight) * 2 + 1;
    console.log(this.sceneController.mouse.x);
    this.sceneController.raycast();
    this.sceneController.render();
};

//this implementation is very ugly and doesn't work as intended
HtmlController.prototype.onDocumentMouseMove = function(event)
{   
    //we can only calculate the distance if there already was a mouse event
    if (typeof(lastMousePosition) != 'undefined') {

        //calculate how far the mouse has moved
        let deltaX = lastMousePosition.x - event.clientX;
        let deltaY = lastMousePosition.y - event.clientY;

        this.sceneController.rotateNode(THREE.Vector3.XAxis, deltaX);
        this.sceneController.rotateNode(THREE.Vector3.XAxis, deltaY);
    }
    //save current position for next time
    lastMousePosition = {
        x : event.clientX,
        y : event.clientY
    };
};

HtmlController.prototype.onDocumentMouseUp = function(event)
{
    
};

HtmlController.prototype.onDocumentKeyDown = function(event) {
    //as alternative to event.key one can use event.which that returns the ASCII codes, e.g., r = 82
    var keyCode = event.key;

    switch(keyCode)
    {
        case "w":
            this.sceneController.selectParent(this.node);
            console.log('w is pressed');
        break;
        case "s":
            this.sceneController.selectChild(this.node);
        break;
        case "a":
            this.sceneController.selectSibling(this.node);
            console.log('a is pressed');
        break;
        case "d":
            console.log('d is pressed');
        break;
        case "c":
            this.sceneController.toggleAxisVisibility();
            break; 
        case "r": // r
            this.sceneController.controls.reset();
            this.sceneController.reset();
            break;
        case "e":
            this.sceneController.selectAll();
            console.log('e is pressed');
        break;
        case "k":
            this.sceneController.toggleSelection();
            console.log('k is pressed');
        break;
        case "h":
            toggleVisibility(document.getElementById("instructions"));
            break;
        case "ArrowUp":
            this.sceneController.rotateNode(THREE.Vector3.XAxis, 20);
            break;
        case "ArrowDown":
            this.sceneController.rotateNode(THREE.Vector3.XAxis, -20);
            break;
        case "ArrowLeft":
            this.sceneController.rotateNode(THREE.Vector3.YAxis, -20);
            break;
        case "ArrowRight":
            this.sceneController.rotateNode(THREE.Vector3.YAxis, 20);
            break;    
        
           
    }
    this.sceneController.render();
};
