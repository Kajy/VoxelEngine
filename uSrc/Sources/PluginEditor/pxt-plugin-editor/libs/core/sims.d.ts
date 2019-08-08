// Auto-generated from simulator. Do not edit.
declare namespace webSocketManager {
    /**
     * Format and save function
     * @param name
     * @param params
     */
    //% promise
    //% shim=webSocketManager::formatFunctionAsync promise
    function formatFunction(name: string, params: object): void;

    /**
     * Executes webSocket to communicate with the client
     * @param name
     * @param params
     */
    //% promise
    //% shim=webSocketManager::initialiseEventAsync promise
    function initialiseEvent(): void;

    /**
     * Executes webSocket to communicate with the client
     * @param name
     * @param params
     */
    //% promise
    //% shim=webSocketManager::sendEventAsync promise
    function sendEvent(type: string, params: object): void;

}

// Auto-generated. Do not edit. Really.
