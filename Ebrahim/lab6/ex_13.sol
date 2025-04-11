// contracts/access-control/Auth.sol
// SPDX-License-Identifier: MIT
pragma solidity >=0.5.0 <0.8.0;   //Only compile this contract with Solidity version 0.5.0 or newer, but not 0.8.0 or above." 

contract Auth {
    address private _administrator;

    constructor(address deployer) {
        // Make the deployer of the contract the administrator
        _administrator = deployer;
    }

    function isAdministrator(address user) public view returns (bool) {
        return user == _administrator;
    }
}