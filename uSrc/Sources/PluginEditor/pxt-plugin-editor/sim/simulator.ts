/// <reference path="../node_modules/pxt-core/built/pxtsim.d.ts"/>

namespace pxsim {
    /**
     * This function gets called each time the program restarts
     */
    initCurrentRuntime = () => {
        runtime.board = new Board();
        
    };

    /**
     * Gets the current 'board', eg. program state.
     */
    export function board() : Board {
        return runtime.board as Board;
    }

    /**
     * Represents the entire state of the executing program.
     * Do not store state anywhere else!
     */
    export class Board extends pxsim.BaseBoard {
        constructor() {
            super();
            
        }
        
        kill() {
            super.kill()
        }

        initAsync(msg: pxsim.SimulatorRunMessage): Promise<void> {
            let address = "localhost";
            let port = "9999";

            webSocketManager.initialiseWebSocket(address, port);
            return Promise.resolve();
        }

    }
}