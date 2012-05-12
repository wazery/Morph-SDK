#Project sub-directories
************************

There are two main sub-directories in the Morph editor, they are:

##MorphCore

Which has all the source and header files for the core sub-systems and base types in the editor. Like:

- MSystemMangae: Which is responsible for creating the Ogre Canvas and managing it along with
all of its resources. It also comunicates with the other sub-systems like MNodeManager for creating
scene nodes. It can be regarded as the main sub-system in the editor.
- MNodeManager: Which is responsible for managing and handling the creation and registeration of
scene nodes.
- MNode: A base type for editor scene nodes.
- MRootNode: Which is the type of the root node which is representing the world environment.
- MLogManager: Which is responsible for logging different types of messages to the user, like
errors and Ogre specific messages.
- MCommandManager: Which is a not yet fully implemented class, it is for future enhancements to
implement the Command Pattern and make Undo/Redo support.
- MAttribute: Base type for object attributes.

##mOgreEntityViewer

Which has all the classes for the editor views, like Logging view and others.