// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

/**
 * DocumentLocker: Minimal decentralized document registry.
 * - Users can add document metadata hashes (e.g., IPFS CID or SHA-256).
 * - Each document has an owner and timestamp.
 * - Owner can revoke a document (soft delete/state change).
 */
contract DocumentLocker {
    struct Document {
        string hash;        // IPFS CID or any hash string
        string name;        // Optional label/title
        uint256 createdAt;  // Block timestamp
        bool active;        // Active/revoked flag
        address owner;      // Owner address
    }

    // docId => Document
    mapping(bytes32 => Document) private documents;
    // owner => list of docIds
    mapping(address => bytes32[]) private ownerDocs;

    event DocumentAdded(bytes32 indexed docId, address indexed owner, string hash, string name);
    event DocumentRevoked(bytes32 indexed docId, address indexed owner);

    /**
     * Derive a stable ID from user + hash.
     */
    function computeDocId(address owner, string memory hash) public pure returns (bytes32) {
        return keccak256(abi.encode(owner, hash));
    }

    /**
     * Add a new document. Fails if already exists and active.
     */
    function addDocument(string calldata hash, string calldata name) external {
        require(bytes(hash).length > 0, "Hash required");

        bytes32 docId = computeDocId(msg.sender, hash);
        Document storage d = documents[docId];

        require(!d.active, "Document already exists");

        documents[docId] = Document({
            hash: hash,
            name: name,
            createdAt: block.timestamp,
            active: true,
            owner: msg.sender
        });

        ownerDocs[msg.sender].push(docId);

        emit DocumentAdded(docId, msg.sender, hash, name);
    }

    /**
     * Revoke an existing document (owner only).
     */
    function revokeDocument(bytes32 docId) external {
        Document storage d = documents[docId];
        require(d.owner == msg.sender, "Not owner");
        require(d.active, "Already revoked");

        d.active = false;

        emit DocumentRevoked(docId, msg.sender);
    }

    /**
     * Read document by ID.
     */
    function getDocument(bytes32 docId)
        external
        view
        returns (string memory hash, string memory name, uint256 createdAt, bool active, address owner)
    {
        Document storage d = documents[docId];
        require(d.owner != address(0), "Not found");
        return (d.hash, d.name, d.createdAt, d.active, d.owner);
    }

    /**
     * List document IDs for an owner.
     */
    function listDocuments(address owner) external view returns (bytes32[] memory) {
        return ownerDocs[owner];
    }
}
