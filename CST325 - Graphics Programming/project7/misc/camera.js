function Camera(input) {
    // The following two parameters will be used to automatically create the cameraWorldMatrix in this.update()
    this.cameraYaw = 0;
    this.cameraPosition = new Vector3();

    this.cameraWorldMatrix = new Matrix4();

    // -------------------------------------------------------------------------
    this.getViewMatrix = function() {
        return this.cameraWorldMatrix.clone().inverse();
    }

    // -------------------------------------------------------------------------
    this.getForward = function() {
        // todo #6 - pull out the forward direction from the world matrix and return as a vector
        //         - recall that the camera looks in the "backwards" direction

        let matrix = this.cameraWorldMatrix.elements;

        let forward = new Vector3(matrix[2], matrix[7], matrix[10]).multiplyScalar(-1);
        return forward;
    }
    // -------------------------------------------------------------------------
    this.update = function(dt) {
        var currentForward = this.getForward();

        if (input.up) {
            // todo #7 - move the camera position a little bit in its forward direction
            let displacement = currentForward.clone().normalize().multiplyScalar(.1);
            this.cameraPosition = this.cameraPosition.add(displacement);
        }

        if (input.down) {
            // todo #7 - move the camera position a little bit in its backward direction
            let displacement = currentForward.clone().normalize().multiplyScalar(.1);
            this.cameraPosition = this.cameraPosition.subtract(displacement);
        }

        if (input.left) {
            // todo #8 - add a little bit to the current camera yaw
            this.cameraYaw = this.cameraYaw + .5;
        }

        if (input.right) {
            // todo #8 - subtract a little bit from the current camera yaw
            this.cameraYaw = this.cameraYaw - .5;
        }

        // todo #7 - create the cameraWorldMatrix from scratch based on this.cameraPosition
        this.cameraWorldMatrix.makeTranslation(this.cameraPosition);

        // todo #8 - create a rotation matrix based on cameraYaw and apply it to the cameraWorldMatrix
        // (order matters!)
        this.cameraWorldMatrix.multiply(this.cameraWorldMatrix.clone().makeRotationY(this.cameraYaw));
    }
}

// EOF 00100001-10