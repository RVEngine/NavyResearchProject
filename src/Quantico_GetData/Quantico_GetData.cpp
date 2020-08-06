#include "Quantico_GetData.h"
#include "Version.h"
#include "Gears.h"
#include "ComponentDirector.h"



//Note:
//This file is partially autogenerated
//It is safe to make modifications to most of the file, however please don't modify the API function signatures
APIResult GEARS_API Component_Initialize(_In_ const char* component_folder)
{
  //GEARS NOTE: Use this function to perform component initialization.
  //Access to other components is unavailable.
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API Component_OnStart(_In_ APIManager_v6* api_manager, _In_ NativeModuleHandle proxy_handle)
{

  //GEARS NOTE: Use this function to connect to other components.
  //Using the specified api_manager variable, this component can request access
  //to APIs that have been registered with Gears.

  //The Gears class will take care of requesting APIs for you. See Gears.h for more details.
  Gears::InitializeAPIs(api_manager, proxy_handle);
 
  Gears::API::LogAPIv1()->SetName(Gears::API::LogAPIv1(), "Quantico_GetData");
  Gears::API::LogAPIv1()->EnableConsoleLog(Gears::API::LogAPIv1());
  Gears::API::LogAPIv1()->EnableColors(Gears::API::LogAPIv1());
  Gears::API::LogAPIv1()->EnableConsoleLog(Gears::API::LogAPIv1());
  Gears::API::LogAPIv1()->EnableDebuggerLog(Gears::API::LogAPIv1());
  Gears::API::LogAPIv1()->SetFilter(Gears::API::LogAPIv1(), kSeverityLevel_Debug);

  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API Component_OnStop()
{
  //GEARS NOTE: Use this function to perform "last chance" functionality.
  //All components are still accessible.

  //Release all APIs and set them to nullptr.
  Gears::ReleaseAPIs();

  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API Component_Shutdown()
{
  //GEARS NOTE: Use this function to cleanup any resources that were allocated.
  //This component's shared library is about to be unloaded.
  //Access to other components is unavailable.
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API Component_IsParallelizable(_Out_ bool32_t* parallelizable)
{
  //GEARS NOTE: Set parallelizable to TRUE to enable this component's OnStart to be called from a spawned thread
  *parallelizable = FALSE;
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API Component_GetName(_Inout_ int32_t* name_length, _Out_opt_ char* name)
{
  //GEARS NOTE: Use this function to fill out the name string with the name of the component.
  //Defaulted to return the official component name
  static const char* kComponentName = "Quantico_GetData";

  if(name_length == nullptr)
  {
    return kAPIResult_ParamsInvalid;
  }

  if(name == nullptr)
  {
    *name_length = static_cast<int32_t>(strlen(kComponentName) + 1);
  }
  else
  {
    strcpy_s(name, *name_length, kComponentName);
  }
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API Component_GetVersion(_Inout_ int32_t* version_length, _Out_opt_ char* version)
{
  //GEARS NOTE: Use this function to fill out the version string with the version of the component.
  //Defaulted to return the auto generated/incremented version from Version.h
  static const char* kVersion = VERSION;

  if(version_length == nullptr)
  {
    return kAPIResult_ParamsInvalid;
  }

  if(version == nullptr)
  {
    *version_length = static_cast<int32_t>(strlen(kVersion) + 1);
  }
  else
  {
    strcpy_s(version, *version_length, kVersion);
  }
  return kAPIResult_GeneralSuccess;
}


//APIResult GEARS_API Mission_GetPlayer(_Out_ ObjectHandle_v3* player)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_StartEmptyMission(_In_ const char* world_name, _In_ bool32_t host_multiplayer)
//{
//    
//  
//    return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_StartMission(_In_ const char* mission_name, _In_ bool32_t host_multiplayer)
//{
//  APIResult StartMission(const char* world_name = "sniper", bool32_t host_multiplayer = TRUE);
//
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_EndMission()
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetElapsedTime(_Out_ float32_t* elapsed_time)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_Play()
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_Pause()
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_IsPlaying(_Out_ bool32_t* is_playing)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_IsPaused(_Out_ bool32_t* is_paused)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_SetPlayable(_In_ ObjectHandle_v3 lifeform, _In_ bool32_t playable)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetPlayable(_In_ ObjectHandle_v3 lifeform, _Out_ bool32_t* playable)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetMissionDirectory(_Out_opt_ char* directory, _Inout_ int32_t* length)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_SetPlayer(_In_ ObjectHandle_v3 lifeform)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetMissionCount(_In_ bool32_t multiplayer, _Out_ int32_t* mission_count)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetMissionName(_In_ int32_t mission_index, _In_ bool32_t multiplayer, _Out_opt_ char* name, _Inout_ int32_t* name_size)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetActiveMissionName(_Out_opt_ char* mission_name, _Inout_ int32_t* mission_name_size)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetActiveMissionMap(_Out_opt_ char* map_name, _Inout_ int32_t* map_name_size)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_SetMapOrigin(_In_ GeoPosition_v5 origin)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetMapOrigin(_Inout_ GeoPosition_v5* origin)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetMissionInfo(_In_ int32_t mission_index, _In_ bool32_t is_multiplayer, _Out_ MissionInfo_v2* mission_info)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetAllPlayers(_Out_opt_ ObjectHandle_v3* buffer, _Inout_ int32_t* buffer_size)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_GetPlayerName(_In_ ObjectHandle_v3 object, _Out_ char* buffer, _Inout_ int32_t* buffer_size)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_IsPlayer(_In_ ObjectHandle_v3 object, _Out_ bool32_t* is_player)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_SaveMission(_In_ const char* save_name)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API Mission_LoadMission(_In_ const char* save_name)
//{
//  return kAPIResult_GeneralSuccess;
//}

APIResult GEARS_API MissionEditor_GetMode(_Out_ MissionEditorMode_v1* mode)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_Open(_In_ const char* map_id, _In_opt_ const GeoPosition_v3* initial_position)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_LoadMission(_In_ const char* mission_name, _In_ bool32_t is_multiplayer)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_SelectObject(_In_ ObjectHandle_v3 object)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_DeselectObject(_In_ ObjectHandle_v3 object)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_CenterCameraOnObject(_In_ ObjectHandle_v3 object)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_TriggerObjectContextMenu(_In_ ObjectHandle_v3 object, _In_opt_ const ScreenPosition_v3* position)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_LoadEmptyMission(_In_ const char* map_id, _In_opt_ const GeoPosition_v3* initial_position)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_CollapseOrbatObject(_In_ ObjectHandle_v3 object, _In_ bool32_t collapse)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_IsCollapsedInOrbat(_In_ ObjectHandle_v3 object, _Out_ bool32_t* collapsed)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_HasAspect(_In_ ObjectHandle_v3 object, _Out_ bool32_t* has_aspect)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_GetObjectProperty(_In_ ObjectHandle_v3 object, _In_ const char* name, _Out_opt_ char* value, _Inout_ int32_t* value_length)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditor_SetObjectProperty(_In_ ObjectHandle_v3 object, _In_ const char* name, _In_ const char* value)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionListener_OnPlayerSwitchedUnits(_In_ ObjectHandle_v3 old_entity, _In_ ObjectHandle_v3 new_entity)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionListener_OnMissionUnload(_In_ const char* mission_name)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionListener_OnMissionStart(_In_ bool32_t restart)
{
  ComponentDirector::Get().OnMissionStart(restart);
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionListener_OnMissionLoad(_In_ const char* mission_name)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionListener_OnMissionEnd(_In_ bool32_t restart)
{
  ComponentDirector::Get().OnMissionEnd(restart);
  return kAPIResult_GeneralSuccess;
}

//APIResult GEARS_API DebugUI_ShowMainWindow(_In_ bool32_t show_main_window)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API DebugUI_SetMainWindowToggleHotkey(_In_ KeyID key_code, _In_ bool32_t control, _In_ bool32_t shift, _In_ bool32_t alt)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API DebugUI_SetGlobalUIScale(_In_ float32_t scale)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API DebugUI_IsMainWindowShown(_Out_ bool32_t* main_window_shown)
//{
//  return kAPIResult_GeneralSuccess;
//}

//APIResult GEARS_API DebugUI_GetGlobalUIScale(_Out_ float32_t* scale)
//{
//  return kAPIResult_GeneralSuccess;
//}

APIResult GEARS_API ControlAIAspect_SetBlackboardVariable(_In_ ObjectHandle_v3 object, _In_ const char* variable, _In_ const char* value, _In_ int32_t value_size)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API ControlAIAspect_SetBehaviorTree(_In_ ObjectHandle_v3 object, _In_ const char* bt_name)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API ControlAIAspect_ReceiveMessage(_In_ ObjectHandle_v3 object, _In_ const char* subject, _In_ const char* parameters, _In_ int32_t parameters_size)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API ControlAIAspect_HasAspect(_In_ ObjectHandle_v3 object, _Out_ bool32_t* has_aspect)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API ControlAIAspect_GetBlackboardVariable(_In_ ObjectHandle_v3 object, _In_ const char* variable, _Out_ char* value, _Inout_ int32_t* value_size)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API ControlAIAspect_GetBehaviorTree(_In_ ObjectHandle_v3 object, _Out_ char* buffer_bt_name, _Inout_ int32_t* buffer_size)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API ApplicationListener_OnBeforeSimulation(_In_ float32_t delta)
{
  ComponentDirector::Get().OnBeforeSimulation(delta);
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API ApplicationListener_OnAfterSimulation(_In_ float32_t delta)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditorListener_OnObjectSelectionChange(_In_ ObjectHandle_v3 object, _In_ bool32_t selected)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditorListener_OnObjectExpandCollapse(_In_ ObjectHandle_v3 object, _In_ bool32_t expanded)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditorListener_OnMapExport(_In_ GeoPosition_v3 begin, _In_ GeoPosition_v3 end, _In_ float32_t scale, _In_ float32_t detail, _In_ MapExportMode_v1 mode, _In_ const MapExportInterface_v1* mei, _In_opt_ const char** layers, _In_opt_ int32_t layer_count)
{
  return kAPIResult_GeneralSuccess;
}

APIResult GEARS_API MissionEditorListener_OnClose()
{
  return kAPIResult_GeneralSuccess;
}

void GEARS_API DebugUIListener_OnRenderMainWindow()
{
    ComponentDirector::Get().OnRenderMainWindow();
}

void GEARS_API DebugUIListener_OnRenderHMDWindow()
{
}

void GEARS_API DebugUIListener_OnRenderCustomWindow()
{
    ComponentDirector::Get().OnRenderCustomWindow();
}

void GEARS_API WorldListener_OnObjectDeletion(_In_ ObjectHandle_v3 object)
{
}

void GEARS_API WorldListener_OnObjectCreation(_In_ ObjectHandle_v3 object)
{
    ComponentDirector::Get().OnObjectCreation(object);
}

void GEARS_API WorldListener_OnLocalObjectPromotion(_In_ ObjectHandle_v3 old_handle, _In_ ObjectHandle_v3 new_handle)
{
}

