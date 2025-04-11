pragma solidity >=0.5 <0.8.0;
//Exercise 1
contract Factory {

}

//Exercise 2
// Our Product ID will be a 16-digit number.
uint idDigits = 16;

//Exercise 3
// Set idModulus equal to 10 raised to the power of idDigits.
uint idModulus = 10 ** idDigits;

//Exercise 4
//Define a struct to represent a Product with a name and an id.
struct Product {
    string name;
        uint id;
}

//Exercise 5
//Create a public array to store all Products.
Product[] products;


//Exercise 6
function _createProduct(string memory _name, uint _id) private {
    // Push the new product to the array
    products.push(Product(_name, _id));
}

//Exercise 7
// Create a private function _generateRandomId that takes a string and returns a uint.
function _generateRandomId(string memory _str) private view returns (uint) {

    
//Exercise 8
// Take the keccak256 hash of the encoded string, typecast it as uint,
    // and return the result modulo idModulus so that the ID is 16 digits.
    // *******************************
    uint rand = uint(keccak256(abi.encodePacked(_str)));
    return rand % idModulus;
}

//Exercise 8
//Create Random Product Function
function createRandomProduct(string memory _name) public {
    uint randId = _generateRandomId(_name);
    _createProduct(_name, randId);
}

// Exercise 9: Events
// Declare an event to notify when a new product is created
event NewProduct(uint ArrayProductId, string name, uint id);


// Exercise 10: Mappings (part 1)
// Mapping from product index to owner address.
mapping(uint => address) public productToOwner;
// Mapping to keep track of how many products an owner has.
mapping(address => uint) public ownerProductCount;

// Exercise 11: Ownership Function
// Create a function to assign ownership of a product to the caller
function Ownership(uint _productId) public {
    productToOwner[_productId] = msg.sender;
    ownerProductCount[msg.sender]++;
}


// Exercise 12: Retrieve Products by Owner
// Create an external view function that returns an array of product indices owned by _owner.
function getProductsByOwner(address _owner) external view returns(uint[] memory) {
    // The number of products the owner owns determines the length of our result array.
    uint count = ownerProductCount[_owner];
    uint[] memory result = new uint[](count);
    uint counter = 0;
    // Loop over all products and check if the owner matches.
    for (uint i = 0; i < products.length; i++) {
        if (productToOwner[i] == _owner) {
            result[counter] = i;
            counter++;
        }
    }
    return result;


}


//Exercise 13: 




//Exercise 14:
// Mapping to store a user’s age based on a numeric user ID.
mapping(uint => uint) public age;
    
// Modifier that checks that the age of a given user ID is at least a certain value.
modifier olderThan(uint _minAge, uint _userId) {
    require(age[_userId] >= _minAge, "User is not old enough");
    _;


