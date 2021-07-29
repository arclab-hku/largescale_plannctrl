
"use strict";

let StreamRate = require('./StreamRate.js')
let SetMode = require('./SetMode.js')
let LogRequestData = require('./LogRequestData.js')
let WaypointPull = require('./WaypointPull.js')
let CommandHome = require('./CommandHome.js')
let MountConfigure = require('./MountConfigure.js')
let CommandTOL = require('./CommandTOL.js')
let FileOpen = require('./FileOpen.js')
let FileChecksum = require('./FileChecksum.js')
let CommandInt = require('./CommandInt.js')
let FileRemoveDir = require('./FileRemoveDir.js')
let LogRequestList = require('./LogRequestList.js')
let WaypointSetCurrent = require('./WaypointSetCurrent.js')
let WaypointPush = require('./WaypointPush.js')
let FileList = require('./FileList.js')
let VehicleInfoGet = require('./VehicleInfoGet.js')
let LogRequestEnd = require('./LogRequestEnd.js')
let WaypointClear = require('./WaypointClear.js')
let FileTruncate = require('./FileTruncate.js')
let CommandTriggerInterval = require('./CommandTriggerInterval.js')
let CommandTriggerControl = require('./CommandTriggerControl.js')
let ParamPush = require('./ParamPush.js')
let FileMakeDir = require('./FileMakeDir.js')
let ParamPull = require('./ParamPull.js')
let CommandVtolTransition = require('./CommandVtolTransition.js')
let CommandBool = require('./CommandBool.js')
let FileRename = require('./FileRename.js')
let SetMavFrame = require('./SetMavFrame.js')
let FileRead = require('./FileRead.js')
let CommandLong = require('./CommandLong.js')
let MessageInterval = require('./MessageInterval.js')
let FileClose = require('./FileClose.js')
let ParamSet = require('./ParamSet.js')
let FileRemove = require('./FileRemove.js')
let ParamGet = require('./ParamGet.js')
let FileWrite = require('./FileWrite.js')

module.exports = {
  StreamRate: StreamRate,
  SetMode: SetMode,
  LogRequestData: LogRequestData,
  WaypointPull: WaypointPull,
  CommandHome: CommandHome,
  MountConfigure: MountConfigure,
  CommandTOL: CommandTOL,
  FileOpen: FileOpen,
  FileChecksum: FileChecksum,
  CommandInt: CommandInt,
  FileRemoveDir: FileRemoveDir,
  LogRequestList: LogRequestList,
  WaypointSetCurrent: WaypointSetCurrent,
  WaypointPush: WaypointPush,
  FileList: FileList,
  VehicleInfoGet: VehicleInfoGet,
  LogRequestEnd: LogRequestEnd,
  WaypointClear: WaypointClear,
  FileTruncate: FileTruncate,
  CommandTriggerInterval: CommandTriggerInterval,
  CommandTriggerControl: CommandTriggerControl,
  ParamPush: ParamPush,
  FileMakeDir: FileMakeDir,
  ParamPull: ParamPull,
  CommandVtolTransition: CommandVtolTransition,
  CommandBool: CommandBool,
  FileRename: FileRename,
  SetMavFrame: SetMavFrame,
  FileRead: FileRead,
  CommandLong: CommandLong,
  MessageInterval: MessageInterval,
  FileClose: FileClose,
  ParamSet: ParamSet,
  FileRemove: FileRemove,
  ParamGet: ParamGet,
  FileWrite: FileWrite,
};
