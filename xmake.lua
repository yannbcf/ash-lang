add_rules("mode.debug", "mode.release")

set_languages("cxx20", "cxx2a")
set_symbols("debug")

add_requires("spdlog")

target("lang")
    set_kind("binary")
    set_pcxxheader("src/stdafx.h")
    add_headerfiles("src/**.h")
    add_files("src/*.cpp")
    add_packages("spdlog")
