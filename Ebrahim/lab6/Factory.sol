// SPDX-License-Identifier: MIT



pragma solidity >=0.5.0 <0.8.0;   //Only compile this contract with Solidity version 0.5.0 or newer, but not 0.8.0 or above." 


contract Factory {                                  //contract 
    uint idDigits = 16;                             
    uint idModulus = 10 ** idDigits;

    struct Product {                    //structure of our product organised by name and id 
        string name;
        uint id;
    }

    Product[] public products; // create array in dynamic mode 

     event NewProduct(uint ArrayProductId, string name, uint id);


    //Ownership mappings
    mapping(uint => address) public productToOwner;
    mapping(address => uint) ownerProductCount;

    function _createProduct(string memory _name, uint _id) private {     // this function is gonna add new product id and name to our array 


        products.push(Product(_name, _id));     // this line gonna add the name and id by using push command 

        uint productId = products.length - 1; /////////// to be recheck 

        products.push(Product(_name, _id));//////////////

        //uint productId = products.push(Product(_name, _id)) - 1;
        emit NewProduct(productId, _name, _id);

        // Track ownership
        productToOwner[productId] = msg.sender;
        ownerProductCount[msg.sender]++;

       // emit NewProduct(productId, _name, _id);
        

    }


    function _generateRandomId(string memory _str) private view returns (uint) {    //view functions can read the blockchain's state (like variables or mappings) but cannot modify it
        uint rand = uint(keccak256(abi.encodePacked(_str)));   //Application Binary Interface.
        return rand % idModulus;
    }

    function createRandomProduct(string memory _name) public {
        uint randId = _generateRandomId(_name);
        _createProduct(_name, randId);
    }

    function Ownership(uint _productId) public {
    productToOwner[_productId] = msg.sender;
    ownerProductCount[msg.sender]++;
    }

    function getProductsByOwner(address _owner) external view returns (uint[] memory) {
    uint counter = 0;
    uint[] memory result = new uint[](ownerProductCount[_owner]);

    for (uint i = 0; i < products.length; i++) {
        if (productToOwner[i] == _owner) {
            result[counter] = i;
            counter++;
        }
    }

    return result;
    }


}






