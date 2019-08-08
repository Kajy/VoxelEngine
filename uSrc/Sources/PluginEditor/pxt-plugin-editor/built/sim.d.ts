/// <reference path="../libs/core/enums.d.ts" />
/// <reference path="../node_modules/pxt-core/built/pxtsim.d.ts" />
declare namespace pxsim.webSocketManager {
    function initialiseWebSocket(adress: string, port: string): Promise<void>;
    function isWebsocketOpen(): void;
    /**
     * Format and save function
     * @param name
     * @param params
     */
    function formatFunctionAsync(name: string, params: object): Promise<void>;
    /**
     * Executes webSocket to communicate with the client
     * @param name
     * @param params
     */
    function initialiseEventAsync(): Promise<void>;
    /**
    * Executes webSocket to communicate with the client
    * @param name
    * @param params
    */
    function sendEventAsync(type: string, params: object): Promise<void>;
}
declare namespace pxsim {
    /**
     * Gets the current 'board', eg. program state.
     */
    function board(): Board;
    /**
     * Represents the entire state of the executing program.
     * Do not store state anywhere else!
     */
    class Board extends pxsim.BaseBoard {
        constructor();
        kill(): void;
        initAsync(msg: pxsim.SimulatorRunMessage): Promise<void>;
    }
}
