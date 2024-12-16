workspace "BoxGame"
    architecture "x64"
    configurations { "Debug", "Release" }
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "BoxGame"
    location "BoxGame"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
        "%{prj.name}/src/**.h", 
        "%{prj.name}/src/**.cpp" 
    }

    includedirs 
    { 
        "%{prj.name}", 
        "%{prj.name}/vendor/Raylib/raylib-5.0_win64_msvc16/include" 
    }

    libdirs 
    { 
        "%{prj.name}/vendor/Raylib/raylib-5.0_win64_msvc16/lib" 
    }

    links 
    { 
        "raylib", 
        "WinMM" 
    }

    filter "system:window"
        systemversion "latest"
        staticruntime "On"
        cppdialect "C++latest"
    
    filter "configurations:Debug"
        defines { "_DEBUG", "_CONSOLE" }
        runtime "Debug"
        symbols "on"