workspace "Hawthorn"
	architecture "x64"
	configurations{ "Debug", "Release", "Dist" }
	startproject "HawthornApp"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "premake5_external.lua"
include "HawthornApp"