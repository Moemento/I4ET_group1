// SPDX-License-Identifier: MIT
pragma solidity >=0.5.0 <0.8.0;   //Only compile this contract with Solidity version 0.5.0 or newer, but not 0.8.0 or above." 

contract UserValidation {
    
    // Public mapping from uint to uint to store user's age
    mapping(uint => uint) public age;

    // Modifier to check if user is older than a certain age
    modifier olderThan(uint _age, uint _userId) {
        require(age[_userId] >= _age, "User is not old enough");
        _;
    }

    // Function that uses the modifier to check if the user is an adult (18+)
    function validationUsers(uint _userId) public view olderThan(18, _userId) {
        // Function body intentionally left blank
    }
}