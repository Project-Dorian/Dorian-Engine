import express, {Express, Request, Response} from "express";

console.log("Initializing HTTP Client Server");
const server: Express = express();
server.use("/", express.static("tools/interface/"));

server.listen(3000, () => {
    console.log("Server Initialized");
});