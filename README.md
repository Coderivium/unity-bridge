Unity Bridge
============

Unity Bridge simplifies using Unity in iOS projects by replacing slow and limited UnitySendMessage function.

To start using bridge you should add CRUnityBridge folder to your XCode project. 
Than add to the Unity C# script which methods you want to invoke the following lines:

    [DllImport("__Internal")]
    public static extern void register_object(IntPtr objectRef, string name);
    
And call this function in Start() method (for MonoBehaviour classes) or constructor:

    register_object((System.IntPtr)GCHandle.Alloc(this);, "ObjectName");
    
Where ObjectName is the name under which you want to access this object.


Now your can call any public method of this class by invoking CRUnityBridge method


    [[[CRUnityBridge] sharedInstance] invokeMethod:"ScriptName:Method" 
                                          onObject:"ObjectName"
                                              args:NULL
                                   returnValueType:NO];
                                   
Where ScriptName is actual name of your Unity scipt.