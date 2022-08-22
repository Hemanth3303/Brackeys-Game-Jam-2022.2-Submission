workspace "Brackeys-Game-Jam-8"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	startproject "Game"

outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	filter "platforms:x64"
		architecture "x86_64"

project "glfw"
	location "%{wks.location}/vendor/glfw"
	language "C"
	cdialect "C17"
	cppdialect "C++20"
	kind "StaticLib"
	targetdir("%{wks.location}/bin/" ..outputdir)
	objdir ("%{wks.location}/bin-int/" ..outputdir)
	systemversion "latest"
	staticruntime "Off"

	includedirs { "%{prj.location}/include" }
	
	files {
	"%{prj.location}/include/GLFW/glfw3.h",
	"%{prj.location}/include/GLFW/glfw3native.h",
	"%{prj.location}/src/internal.h",
	"%{prj.location}/src/platform.h",
	"%{prj.location}/src/mappings.h",
	"%{prj.location}/src/context.c",
	"%{prj.location}/src/init.c",
	"%{prj.location}/src/input.c",
	"%{prj.location}/src/monitor.c",
	"%{prj.location}/src/vulkan.c",
	"%{prj.location}/src/window.c",
	"%{prj.location}/src/egl_context.c",
	"%{prj.location}/src/osmesa_context.c",
	}
	filter "system:linux"
		pic "On"

		files {
			"%{prj.location}/src/x11_init.c",
			"%{prj.location}/src/x11_monitor.c",
			"%{prj.location}/src/x11_window.c",
			"%{prj.location}/src/xkb_unicode.c",
			"%{prj.location}/src/posix_time.c",
			"%{prj.location}/src/posix_thread.c",
			"%{prj.location}/src/glx_context.c",
			"%{prj.location}/src/egl_context.c",
			"%{prj.location}/src/osmesa_context.c",
			"%{prj.location}/src/linux_joystick.c"
		}

		defines {
			"_GLFW_X11"
		}

	filter "system:windows"

		files {
			"%{prj.location}/src/win32_init.c",
			"%{prj.location}/src/win32_joystick.c",
			"%{prj.location}/src/win32_monitor.c",
			"%{prj.location}/src/win32_time.h",
			"%{prj.location}/src/win32_time.c",
			"%{prj.location}/src/win32_thread.h",
			"%{prj.location}/src/win32_thread.c",
			"%{prj.location}/src/win32_window.c",
			"%{prj.location}/src/wgl_context.c",
			"%{prj.location}/src/egl_context.c",
			"%{prj.location}/src/osmesa_context.c"
		}

		defines  { 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

project "glad"
	kind "StaticLib"
	language "C"
	cdialect "C17"
	cppdialect "C++20"
	location "%{wks.location}/vendor/glad"
	targetdir("%{wks.location}/bin/" ..outputdir)
	objdir ("%{wks.location}/bin-int/" ..outputdir)
	staticruntime "Off"
	systemversion "latest"

	files { "%{prj.location}/src/glad.c" }
	includedirs { "%{prj.location}/include/" }

project "stb_image"
	kind "StaticLib"
	language "C"
	cdialect "C17"
	cppdialect "C++20"
	location "%{wks.location}/vendor/stb_image"
	targetdir("%{wks.location}/bin/" ..outputdir)
	objdir ("%{wks.location}/bin-int/" ..outputdir)
	staticruntime "Off"
	systemversion "latest"

	files { "%{prj.location}/src/stb_image.c" }
	includedirs { "%{prj.location}/include/" }

project "Game"
	location "%{wks.location}/Game"
	language "C++"
	cppdialect "C++20"
	cdialect "C17"
	targetdir("%{wks.location}/bin/" ..outputdir)
	objdir ("%{wks.location}/bin-int/" ..outputdir)
	staticruntime "Off"
	systemversion "latest"
	targetname "Game"

	vpaths {
		["Header Files"] = { "**.h", "**.hpp"},
		["Source Files"] = {"**.c", "**.cpp"},
	}
	
	files { 
		"%{prj.location}/src/**.c",
		"%{prj.location}/src/**.cpp",
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.hpp",
		"%{prj.location}/res/**.glsl"
	}
	includedirs {
		"%{prj.location}/src",
		"vendor/glfw/include",
		"vendor/glad/include/",
		"vendor/stb_image/include"
	}

	links { "glfw", "glad", "stb_image" }

	filter { "configurations:Debug", "system:windows", "action:vs*" }
		defines { "_CRT_SECURE_NO_WARNINGS" }

	filter { "configurations:Release", "system:windows", "action:vs*" }
		defines { "_CRT_SECURE_NO_WARNINGS" }

	filter { "action: not vs*", "configurations:Release" }
		buildoptions { "-std=c++20", "-Os" }

	filter { "action: not vs*", "configurations:Debug" }
		buildoptions { "-std=c++20" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		kind "ConsoleApp"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		kind "WindowedApp"
		entrypoint "mainCRTStartup"

	filter "system:windows"
		links { "winmm", "kernel32", "opengl32", "kernel32", "gdi32" }
	filter "system:linux"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}
