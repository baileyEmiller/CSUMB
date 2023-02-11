/* Names: Bailey Miller, Miguel Angel Francisco
 * Stating: I doubt our code is exactly the same
 *
 * An "object" representing a 3d vector to make operations simple and concise.
 *
 * Similar to how we work with plain numbers, we will work with vectors as
 * an entity unto itself.  Note the syntax below: var Vector3 = function...
 * This is different than you might be used to in most programming languages.
 * Here, the function is meant to be instantiated rather than called and the
 * instantiation process IS similar to other object oriented languages => new Vector3()
 */

var Vector3 = function(x, y, z) {
  //this.x = 0; this.y = 0; this.z = 0; 
  this.x = x; this.y = y; this.z = z;

  // Sanity check to prevent accidentally using this as a normal function call
  if (!(this instanceof Vector3)) {
    console.error("Vector3 constructor must be called with the 'new' operator");
  }

  // (done) todo - make sure to set a default value in case x, y, or z is not passed in
  if(this.x == null){
    this.x = 0;
  }
  if(this.y == null){
    this.y = 0;
  }
  if(this.z == null){
    this.z = 0;
  }
}

Vector3.prototype = {

  //----------------------------------------------------------------------------- 
  set: function(x, y, z) {
    // (done) todo set 'this' object's values to those from x, y, and z
    this.x = x; this.y = y; this.z = z;
    return this;
  },

  //----------------------------------------------------------------------------- 
  clone: function() {
    return new Vector3(this.x, this.y, this.z);
  },

  //----------------------------------------------------------------------------- 
  copy: function(other) {
    this.x = other.x; this.y = other.y; this.z = other.z;
    // (done) copy the values from other into 'this'
    return this;
  },

  //----------------------------------------------------------------------------- 
  negate: function() {
    // (done) multiply 'this' vector by -1
    // This SHOULD change the values of this.x, this.y, and this.z
    this.x = this.x * (-1); this.y = this.y * (-1); this.z = this.z * (-1);
    return this;
  },

  //----------------------------------------------------------------------------- 
  add: function(v) {
    // (done) todo - add v to 'this' vector
    // This SHOULD change the values of this.x, this.y, and this.z
    this.x = this.x + v.x; this.y = this.y + v.y; this.z = this.z + v.z;
    return this;
  },

  //----------------------------------------------------------------------------- 
  subtract: function(v) {
    // (done) todo - subtract v from 'this' vector
    // This SHOULD change the values of this.x, this.y, and this.z
    this.x = this.x - v.x; this.y = this.y - v.y; this.z = this.z - v.z;
    return this;
  },

  //----------------------------------------------------------------------------- 
  multiplyScalar: function(scalar) {
    // (done) multiply 'this' vector by "scalar"
    // This SHOULD change the values of this.x, this.y, and this.z
    this.x = this.x * scalar; this.y = this.y * scalar; this.z = this.z * scalar;
    return this;
  },

  //----------------------------------------------------------------------------- 
  length: function() {
    // todo - return the magnitude (A.K.A. length) of 'this' vector
    // This should NOT change the values of this.x, this.y, and this.z
    var xToY = (this.x * this.x) + (this.y * this.y);
    var vectorInstance = xToY + (this.z * this.z);
    return Math.sqrt(vectorInstance);
  },

  //----------------------------------------------------------------------------- 
  lengthSqr: function() {
    // (done) todo - return the squared magnitude of this vector ||v||^2
    // This should NOT change the values of this.x, this.y, and this.z

    // There are many occasions where knowing the exact length is unnecessary 
    // and the square can be substituted instead (for performance reasons).  
    // This function should not have to take the square root of anything.
    var xToY = (this.x * this.x) + (this.y * this.y);
    var vectorInstance = xToY + (this.z * this.z);
    return vectorInstance;
  },

  //----------------------------------------------------------------------------- 
  normalize: function() {
    // (done) todo - Change the components of this vector so that its magnitude will equal 1.
    // This SHOULD change the values of this.x, this.y, and this.z
    var tempLength = this.length();
    this.x = (this.x / tempLength); this.y = (this.y / tempLength); this.z = (this.z / tempLength); //This had me stuck for a fat second
    return this;
  },

  //----------------------------------------------------------------------------- 
  dot: function(other) {
    // (done) todo - return the dot product between this vector and "other"
    // This should NOT change the values of this.x, this.y, and this.z
    var ab = this.length() * other.length();
    return ab;
  },


  //============================================================================= 
  // The functions below must be completed in order to receive an "A"

  //----------------------------------------------------------------------------- 
  fromTo: function(fromPoint, toPoint) {
    if (!(fromPoint instanceof Vector3) || !(toPoint instanceof Vector3)) {
      console.error("fromTo requires to vectors: 'from' and 'to'");
    }

    // (done) todo - return the vector that goes from "fromPoint" to "toPoint"
    //        NOTE - "fromPoint" and "toPoint" should not be altered
    
    return new Vector3(toPoint.x - fromPoint.x, toPoint.y - fromPoint.y, toPoint.z - fromPoint.z);
  },

  //----------------------------------------------------------------------------- 
  project: function(vectorToProject, otherVector) {
    // todo - return a vector that points in the same direction as "otherVector"
    //        but whose length is the projection of "vectorToProject" onto "otherVector"
    //        NOTE - "vectorToProject" and "otherVector" should NOT be altered (i.e. use clone)
    //        See class slides or visit https://en.wikipedia.org/wiki/Vector_projection for more detail.

    var tempV = new Vector3(otherVector.x, otherVector.y, otherVector.z);
    tempV.normalize();
    
    return tempV;
  }
};

// EOF 00100001-10
