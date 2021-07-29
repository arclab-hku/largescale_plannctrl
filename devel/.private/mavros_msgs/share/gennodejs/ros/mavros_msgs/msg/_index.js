
"use strict";

let GPSRTK = require('./GPSRTK.js');
let ParamValue = require('./ParamValue.js');
let HomePosition = require('./HomePosition.js');
let HilActuatorControls = require('./HilActuatorControls.js');
let OpticalFlowRad = require('./OpticalFlowRad.js');
let ESCStatus = require('./ESCStatus.js');
let RadioStatus = require('./RadioStatus.js');
let StatusText = require('./StatusText.js');
let Mavlink = require('./Mavlink.js');
let State = require('./State.js');
let HilSensor = require('./HilSensor.js');
let CommandCode = require('./CommandCode.js');
let ESCInfo = require('./ESCInfo.js');
let WaypointReached = require('./WaypointReached.js');
let GlobalPositionTarget = require('./GlobalPositionTarget.js');
let Waypoint = require('./Waypoint.js');
let Thrust = require('./Thrust.js');
let MountControl = require('./MountControl.js');
let Altitude = require('./Altitude.js');
let ESCInfoItem = require('./ESCInfoItem.js');
let ESCStatusItem = require('./ESCStatusItem.js');
let WaypointList = require('./WaypointList.js');
let LogEntry = require('./LogEntry.js');
let OnboardComputerStatus = require('./OnboardComputerStatus.js');
let Param = require('./Param.js');
let FileEntry = require('./FileEntry.js');
let HilControls = require('./HilControls.js');
let HilStateQuaternion = require('./HilStateQuaternion.js');
let PositionTarget = require('./PositionTarget.js');
let TimesyncStatus = require('./TimesyncStatus.js');
let AttitudeTarget = require('./AttitudeTarget.js');
let ADSBVehicle = require('./ADSBVehicle.js');
let WheelOdomStamped = require('./WheelOdomStamped.js');
let VehicleInfo = require('./VehicleInfo.js');
let Trajectory = require('./Trajectory.js');
let VFR_HUD = require('./VFR_HUD.js');
let HilGPS = require('./HilGPS.js');
let RTKBaseline = require('./RTKBaseline.js');
let CompanionProcessStatus = require('./CompanionProcessStatus.js');
let ExtendedState = require('./ExtendedState.js');
let OverrideRCIn = require('./OverrideRCIn.js');
let Vibration = require('./Vibration.js');
let DebugValue = require('./DebugValue.js');
let LandingTarget = require('./LandingTarget.js');
let LogData = require('./LogData.js');
let ActuatorControl = require('./ActuatorControl.js');
let GPSRAW = require('./GPSRAW.js');
let RTCM = require('./RTCM.js');
let PlayTuneV2 = require('./PlayTuneV2.js');
let ManualControl = require('./ManualControl.js');
let EstimatorStatus = require('./EstimatorStatus.js');
let CamIMUStamp = require('./CamIMUStamp.js');
let RCOut = require('./RCOut.js');
let BatteryStatus = require('./BatteryStatus.js');
let RCIn = require('./RCIn.js');

module.exports = {
  GPSRTK: GPSRTK,
  ParamValue: ParamValue,
  HomePosition: HomePosition,
  HilActuatorControls: HilActuatorControls,
  OpticalFlowRad: OpticalFlowRad,
  ESCStatus: ESCStatus,
  RadioStatus: RadioStatus,
  StatusText: StatusText,
  Mavlink: Mavlink,
  State: State,
  HilSensor: HilSensor,
  CommandCode: CommandCode,
  ESCInfo: ESCInfo,
  WaypointReached: WaypointReached,
  GlobalPositionTarget: GlobalPositionTarget,
  Waypoint: Waypoint,
  Thrust: Thrust,
  MountControl: MountControl,
  Altitude: Altitude,
  ESCInfoItem: ESCInfoItem,
  ESCStatusItem: ESCStatusItem,
  WaypointList: WaypointList,
  LogEntry: LogEntry,
  OnboardComputerStatus: OnboardComputerStatus,
  Param: Param,
  FileEntry: FileEntry,
  HilControls: HilControls,
  HilStateQuaternion: HilStateQuaternion,
  PositionTarget: PositionTarget,
  TimesyncStatus: TimesyncStatus,
  AttitudeTarget: AttitudeTarget,
  ADSBVehicle: ADSBVehicle,
  WheelOdomStamped: WheelOdomStamped,
  VehicleInfo: VehicleInfo,
  Trajectory: Trajectory,
  VFR_HUD: VFR_HUD,
  HilGPS: HilGPS,
  RTKBaseline: RTKBaseline,
  CompanionProcessStatus: CompanionProcessStatus,
  ExtendedState: ExtendedState,
  OverrideRCIn: OverrideRCIn,
  Vibration: Vibration,
  DebugValue: DebugValue,
  LandingTarget: LandingTarget,
  LogData: LogData,
  ActuatorControl: ActuatorControl,
  GPSRAW: GPSRAW,
  RTCM: RTCM,
  PlayTuneV2: PlayTuneV2,
  ManualControl: ManualControl,
  EstimatorStatus: EstimatorStatus,
  CamIMUStamp: CamIMUStamp,
  RCOut: RCOut,
  BatteryStatus: BatteryStatus,
  RCIn: RCIn,
};
