Flexure Communication
=====================

Data Organization
-----------------
```
\ -- (no value)
|
+--fruits -- Number, '5'
|  |
|  +-- apple -- String, 'red'
|  |
|  +-- banana -- String, 'yellow'
|
+--vegetables -- (no value)
   |
   +-- squash -- Number, '3'
   |
   +-- carrot -- Boolean, 'True'
```
Data in Flexure is organized into a global hierarchy/tree.  The root element, or '\', is the highest level of this hierarchy.  Below this are named subelements.  Each element can contain one or more child elements and a single datum.

The datum is a tuple of two byte arrays, a string type and an arbitrarily coded value.  This string type can have any value, but there are several 'standard' types that all Flexure implementations should support.

Note that this is *not* representative of how data is stored internally or transmitted, only how it is organized through the API.

  * TODO: Regex for valid namespace strings
  * TODO: Table of special characters/namespace string resolution

Data Replication
----------------
```
Node A1 <--                                             --> Node D2
Node B1 <--> Datastore 1 <-> Transport <-> Datastore 2 <--> Node E2
Node C1 <--                                             --> Node F2
```
Data in the global hierarchy is replicated between Nodes through the use of Datastores and Transports.  Each of these objects is more formally defined below.  When you write software, you will interact with Nodes and use them to configure Datastores and Transports.

Node
----
The primary mechanism for interacting with Flexure is a Node.  Nodes are native objects that provide access to data stored in Flexure.  One process can have many Nodes, and they will not interfere with each other.  This can be useful in cases where each Node has different settings.  Nodes provide access to values in the global hierarchy, and also track which pieces of data are being used in that hierarchy.

Datastore
---------
Each node in Flexure is connected to a single datastore either through shared memory or in-process memory.  The datastore contains an aggregation of the latest data that has been accumulated from various transports.  It can be shared by more than one Flexure node, and usually will be in many cases.  The transports that the datastore uses are configured from the union of the settings of the individual Nodes attached to the datastore.

Transport
---------
A Transport is a mechanism for exchanging data betweeen Datastores.  Because datastores know a large amount about what data they contain and what they need to update, transports have relatively few responsibilities.  A Transport needs to be able to:

  * Uniquely address each datastore.
  * Send and receive byte array messages transactionally (but not necessarily reliably).

Data Transmission
-----------------
There are four steps to Flexure communication:
 * Discovery
 * Transport connection
 * Schema intersection
 * Data exchange

Discovery
---------
Each node has a number of discovery protocols.  A discovery protocol is a mechanism for detecting other nodes that are sending or receiving data.  A node must discover other transports that can be used to connect to peers.  This protocol can be something automated, like a multicast protocol, or something fixed, like a list of peers' IP addresses.

Each discovery protocol runs in parallel and is assumed to have its own mechanisms for connecting and enumerating itself.  For the purposes of this document, there is only one thing that the discovery protocol needs to specify:

```c++
class DiscoveryProtocol
{
 public:
  virtual Flexure::Transport DiscoveryProtocol::Update();
};
```

Transport
---------
When another transport is found, a flexure node can choose to connect to it.  Transports are assumed to have the following properties:


Schema intersection
-------------------
Flexure represents data as a massive hierarchy.  So when a transport connection is made, the first thing to do is exchange the schema of each side to establish a common protocol for exchanging information.  Upon opening a transport connection, the opening node sends a JSON schema document to the other node containing its schema.  

This schema is limited to some depth, in case something like a quad-tree is being represented.



