/// <reference path="../libs/core/enums.d.ts"/>

namespace pxsim.webSocketManager {
    let socket: WebSocket;
    let websocketOpen: boolean = false;
    let functionToSave: any = null;
    let conditionToSave: any = null;
    let eventToSave: any = null;

    export async function initialiseWebSocket(adress: string, port: string) {
        eventToSave = {
            events: []
        };
        functionToSave = [];
        try {
            socket = new WebSocket('ws://localhost:9999');
        } catch (exception) {
            console.error(exception);
        }

        socket.onopen = function () {
            console.log("Connexion établie.");
            websocketOpen = true;
        };

        // Error on connection
        socket.onerror = function (error) {
            console.log("erreur");
            console.error(error);
        };
    }

    export function isWebsocketOpen() {
        websocketOpen = true;
    }

    function sendMessage(msg: string) {
        // Wait until the state of the socket is not ready and send the message when it is...
        waitForSocketConnection(socket, function () {
            console.log(`On envois : ${msg}`);
            socket.send(msg + '\0');
        });
    }

    // Make the function wait until the connection is made...
    function waitForSocketConnection(ws: any, callback: Function) {
        setTimeout(
            function () {
                if (socket.readyState === 1) {
                    console.log("Connection établie")
                    if (callback != null) {
                        callback();
                    }
                    return;
                } else {
                    console.log("wait for connection...")
                    waitForSocketConnection(ws, callback);
                }
            }, 2);
    };


    /**
     * Parse data inside object typescript
     * @param Obj
     */
    function parseData(Obj: object) {
        var result: object[] = new Array(Obj.length);
        for (var i = 0; i < Obj.length; i++) {
            result[i] = {
                type: 0,
                value: 0,
                name: 0
            };
            for (var j = 0; j < Obj[i].data.length; j++) {
                result[i] = {
                    "type": (Obj[i].data[j].key === "type") ? Obj[i].data[j].val : result[i].type,
                    "value": (Obj[i].data && Obj[i].data[j].key === "value") ? Obj[i].data[j].val : result[i].value,
                    "name": (Obj[i].data && Obj[i].data[j].key === "name") ? Obj[i].data[j].val : result[i].name
                };
            }
        };
        return (result);
    };

    /**
     * Format and save function
     * @param name
     * @param params
     */
    //% promise
    export function formatFunctionAsync(name: string, value: string, type: string, params: object): Promise<void> {
        if (functionToSave === null)
            functionToSave = [];
        if (params && conditionToSave === null)
            functionToSave.push(
                {
                    name,
                    "parameters": parseData(params.data[0].val.data)
                });
        else if (params && conditionToSave) {
            functionToSave.push(
                {
                    name: value,
                    type: "function",
                    value: name,
                    "parameters": parseData(params.data[0].val.data)
                });
        }
        else
            functionToSave.push(
                {
                    name,
                });
        return Promise.resolve();
    };

    /**
  * Format and save condition
  * @param name
  * @param params
  */
    //% promise
    export function formatConditionAsync(name: string, type: string, value: string, params: object): Promise<void> {
        if (functionToSave === null)
            functionToSave = [];
        if (conditionToSave && conditionToSave[0].parameters.parameters)
            var tmpFunctionToSave = parseData(conditionToSave[0].parameters.parameters);
        functionToSave.push(
            {
                name,
                type,
                value,
                "parameters": parseData(params.data[0].val.data)
            });
        if (conditionToSave === null) {
            conditionToSave = [];
            conditionToSave.push(
                {
                    name: "if",
                    "parameters": functionToSave,
                });
        }
        else {
            conditionToSave.push(
                    {
                        name: "if",
                        "parameters": functionToSave,
                    });
         }
        return Promise.resolve();
    };

    /**
     * Executes webSocket to communicate with the client
     * @param name
     * @param params
     */
    //% promise
    export function initialiseEventAsync(): Promise<void> {
        functionToSave = null;
        return Promise.resolve();
    };

    /**
    * Executes webSocket to communicate with the client
    * @param name
    * @param params
    */
    //% promise
    export function sendEventAsync(type: string, params: object): Promise<void> {
        if (params.data[0])
            eventToSave.events.push
                ({
                    "type": type,
                    "parameters": parseData(params.data[0].val.data),
                    functions: conditionToSave ? conditionToSave : functionToSave,
                });
        else
            eventToSave.events.push
                ({
                    "type": type,
                    functions: conditionToSave ? conditionToSave : functionToSave,
                });
            conditionToSave = null;

        // Send a message to server.
        sendMessage(JSON.stringify(eventToSave));
        return Promise.resolve();
    };
}
