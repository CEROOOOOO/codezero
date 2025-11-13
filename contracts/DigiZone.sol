// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

contract DigiZone {
    struct Credential {
        string ipfsHash;
        uint256 issuedAt;
        bool revoked;
    }

    mapping(address => string) public dids;
    mapping(address => Credential[]) public credentials;

    event DIDRegistered(address indexed user, string did);
    event CredentialIssued(address indexed user, string ipfsHash);
    event CredentialRevoked(address indexed user, uint256 index);

    function registerDID(string memory did) public {
        dids[msg.sender] = did;
        emit DIDRegistered(msg.sender, did);
    }

    function issueCredential(string memory ipfsHash) public {
        credentials[msg.sender].push(Credential(ipfsHash, block.timestamp, false));
        emit CredentialIssued(msg.sender, ipfsHash);
    }

    function revokeCredential(uint256 index) public {
        require(index < credentials[msg.sender].length, "Invalid index");
        credentials[msg.sender][index].revoked = true;
        emit CredentialRevoked(msg.sender, index);
    }

    function getCredentials(address user) public view returns (Credential[] memory) {
        return credentials[user];
    }
}