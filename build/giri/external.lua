-- ///////////////////////////////////
-- ///////////////////////////////////
-- ///////////////////////////////////
-- WARNING
-- This file has been auto-generated.
-- Do NOT make modifications directly to it as they will be overwritten!
-- ///////////////////////////////////
-- ///////////////////////////////////
-- ///////////////////////////////////

-- Project names:
local base_name = 'Quantico_GetData'
local component_project_name = base_name
local library_project_name = base_name .. 'Library'
local unittest_project_name = base_name .. 'UnitTest'

-- Projects:
if _ACTION == 'vs2010' then
externalproject( component_project_name )
  location ( project_root .. 'vs2010' )
  uuid ( '276b43dc-fab0-4e94-8264-bb9de015dc64' )
  kind ( 'SharedLib' )
  language ( 'C++' )

externalproject( library_project_name )
  location ( project_root .. 'vs2010' )
  uuid ( '4f95a676-54c8-4ea2-baaf-84c0ef0f4d7b' )
  kind ( 'StaticLib' )
  language ( 'C++' )

externalproject( unittest_project_name )
  location ( project_root .. 'vs2010' )
  uuid ( '04511d2c-37f5-4a1b-9778-6276a2ff868e' )
  kind ( 'ConsoleApp' )
  language ( 'C++' )
end

if _ACTION == 'vs2012' then
externalproject( component_project_name )
  location ( project_root .. 'vs2012' )
  uuid ( '276b43dc-fab0-4e94-8264-bb9de015dc64' )
  kind ( 'SharedLib' )
  language ( 'C++' )

externalproject( library_project_name )
  location ( project_root .. 'vs2012' )
  uuid ( '4f95a676-54c8-4ea2-baaf-84c0ef0f4d7b' )
  kind ( 'StaticLib' )
  language ( 'C++' )

externalproject( unittest_project_name )
  location ( project_root .. 'vs2012' )
  uuid ( '04511d2c-37f5-4a1b-9778-6276a2ff868e' )
  kind ( 'ConsoleApp' )
  language ( 'C++' )
end

if _ACTION == 'vs2013' then
externalproject( component_project_name )
  location ( project_root .. 'vs2013' )
  uuid ( '276b43dc-fab0-4e94-8264-bb9de015dc64' )
  kind ( 'SharedLib' )
  language ( 'C++' )

externalproject( library_project_name )
  location ( project_root .. 'vs2013' )
  uuid ( '4f95a676-54c8-4ea2-baaf-84c0ef0f4d7b' )
  kind ( 'StaticLib' )
  language ( 'C++' )

externalproject( unittest_project_name )
  location ( project_root .. 'vs2013' )
  uuid ( '04511d2c-37f5-4a1b-9778-6276a2ff868e' )
  kind ( 'ConsoleApp' )
  language ( 'C++' )
end

if _ACTION == 'vs2015' then
externalproject( component_project_name )
  location ( project_root .. 'vs2015' )
  uuid ( '276b43dc-fab0-4e94-8264-bb9de015dc64' )
  kind ( 'SharedLib' )
  language ( 'C++' )

externalproject( library_project_name )
  location ( project_root .. 'vs2015' )
  uuid ( '4f95a676-54c8-4ea2-baaf-84c0ef0f4d7b' )
  kind ( 'StaticLib' )
  language ( 'C++' )

externalproject( unittest_project_name )
  location ( project_root .. 'vs2015' )
  uuid ( '04511d2c-37f5-4a1b-9778-6276a2ff868e' )
  kind ( 'ConsoleApp' )
  language ( 'C++' )
end

if _ACTION == 'vs2017' then
externalproject( component_project_name )
  location ( project_root .. 'vs2017' )
  uuid ( '276b43dc-fab0-4e94-8264-bb9de015dc64' )
  kind ( 'SharedLib' )
  language ( 'C++' )

externalproject( library_project_name )
  location ( project_root .. 'vs2017' )
  uuid ( '4f95a676-54c8-4ea2-baaf-84c0ef0f4d7b' )
  kind ( 'StaticLib' )
  language ( 'C++' )

externalproject( unittest_project_name )
  location ( project_root .. 'vs2017' )
  uuid ( '04511d2c-37f5-4a1b-9778-6276a2ff868e' )
  kind ( 'ConsoleApp' )
  language ( 'C++' )
end

if _ACTION == 'vs2019' then
externalproject( component_project_name )
  location ( project_root .. 'vs2019' )
  uuid ( '276b43dc-fab0-4e94-8264-bb9de015dc64' )
  kind ( 'SharedLib' )
  language ( 'C++' )

externalproject( library_project_name )
  location ( project_root .. 'vs2019' )
  uuid ( '4f95a676-54c8-4ea2-baaf-84c0ef0f4d7b' )
  kind ( 'StaticLib' )
  language ( 'C++' )

externalproject( unittest_project_name )
  location ( project_root .. 'vs2019' )
  uuid ( '04511d2c-37f5-4a1b-9778-6276a2ff868e' )
  kind ( 'ConsoleApp' )
  language ( 'C++' )
end

