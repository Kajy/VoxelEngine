var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : new P(function (resolve) { resolve(result.value); }).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (_) try {
            if (f = 1, y && (t = y[op[0] & 2 ? "return" : op[0] ? "throw" : "next"]) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [0, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
var __extends = (this && this.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
/// <reference path="../libs/core/enums.d.ts"/>
var pxsim;
(function (pxsim) {
    var webSocketManager;
    (function (webSocketManager) {
        var socket;
        var websocketOpen = false;
        var functionToSave = null;
        var eventToSave = null;
        function initialiseWebSocket(adress, port) {
            return __awaiter(this, void 0, void 0, function () {
                return __generator(this, function (_a) {
                    eventToSave = {
                        events: []
                    };
                    functionToSave = [];
                    try {
                        socket = new WebSocket('ws://localhost:9999');
                    }
                    catch (exception) {
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
                    return [2 /*return*/];
                });
            });
        }
        webSocketManager.initialiseWebSocket = initialiseWebSocket;
        function isWebsocketOpen() {
            websocketOpen = true;
        }
        webSocketManager.isWebsocketOpen = isWebsocketOpen;
        function sendMessage(msg) {
            // Wait until the state of the socket is not ready and send the message when it is...
            waitForSocketConnection(socket, function () {
                console.log("On envois : " + msg);
                socket.send(msg + '\0');
            });
        }
        // Make the function wait until the connection is made...
        function waitForSocketConnection(ws, callback) {
            setTimeout(function () {
                if (socket.readyState === 1) {
                    console.log("Connection établie");
                    if (callback != null) {
                        callback();
                    }
                    return;
                }
                else {
                    console.log("wait for connection...");
                    waitForSocketConnection(ws, callback);
                }
            }, 2);
        }
        ;
        /**
         * Parse data inside object typescript
         * @param Obj
         */
        function parseData(Obj) {
            var result = new Array(Obj.length);
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
            }
            ;
            return (result);
        }
        ;
        /**
         * Format and save function
         * @param name
         * @param params
         */
        //% promise
        function formatFunctionAsync(name, params) {
            if (functionToSave === null)
                functionToSave = [];
            functionToSave.push({
                name: name,
                "parameters": parseData(params.data[0].val.data)
            });
            return Promise.resolve();
        }
        webSocketManager.formatFunctionAsync = formatFunctionAsync;
        ;
        /**
         * Executes webSocket to communicate with the client
         * @param name
         * @param params
         */
        //% promise
        function initialiseEventAsync() {
            functionToSave = null;
            return Promise.resolve();
        }
        webSocketManager.initialiseEventAsync = initialiseEventAsync;
        ;
        /**
        * Executes webSocket to communicate with the client
        * @param name
        * @param params
        */
        //% promise
        function sendEventAsync(type, params) {
            if (params.data[0])
                eventToSave.events.push({
                    "type": type,
                    "parameters": parseData(params.data[0].val.data),
                    functions: functionToSave,
                });
            else
                eventToSave.events.push({
                    "type": type,
                    functions: functionToSave,
                });
            // Send a message to server.
            sendMessage(JSON.stringify(eventToSave));
            return Promise.resolve();
        }
        webSocketManager.sendEventAsync = sendEventAsync;
        ;
    })(webSocketManager = pxsim.webSocketManager || (pxsim.webSocketManager = {}));
})(pxsim || (pxsim = {}));
/// <reference path="../node_modules/pxt-core/built/pxtsim.d.ts"/>
var pxsim;
(function (pxsim) {
    /**
     * This function gets called each time the program restarts
     */
    pxsim.initCurrentRuntime = function () {
        pxsim.runtime.board = new Board();
    };
    /**
     * Gets the current 'board', eg. program state.
     */
    function board() {
        return pxsim.runtime.board;
    }
    pxsim.board = board;
    /**
     * Represents the entire state of the executing program.
     * Do not store state anywhere else!
     */
    var Board = /** @class */ (function (_super) {
        __extends(Board, _super);
        function Board() {
            return _super.call(this) || this;
        }
        Board.prototype.kill = function () {
            _super.prototype.kill.call(this);
        };
        Board.prototype.initAsync = function (msg) {
            var address = "localhost";
            var port = "9999";
            pxsim.webSocketManager.initialiseWebSocket(address, port);
            return Promise.resolve();
        };
        return Board;
    }(pxsim.BaseBoard));
    pxsim.Board = Board;
})(pxsim || (pxsim = {}));
