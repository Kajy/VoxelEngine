/// <reference path="../node_modules/pxt-core/built/pxteditor.d.ts" />
var pxt;
(function (pxt) {
    var editor;
    (function (editor) {
        editor.initExtensionsAsync = function (opts) {
            pxt.debug('loading pxt-j5 target extensions...');
            var res = {
                /* called when user presses the save button */
                saveProjectAsync: function (res) {
                    var port = 3074;
                    return pxt.Util.httpPostJsonAsync("http://localhost:" + port + "/save", res)
                        .then(function () { });
                }
            };
            return Promise.resolve(res);
        };
    })(editor = pxt.editor || (pxt.editor = {}));
})(pxt || (pxt = {}));
