add_executable(${example_name}
    main.cpp
)

## UNCOMMENT TO USE .a file in libs folder
#find_library(my_external_lib mylib libs)

## UNCOMMENT to use sourcecode
#add_subdirectory(/path/to/my/lib/infrared)

target_link_libraries(${example_name}
    infrared
)

pico_set_program_description(${example_name} ${desc})
pico_set_program_version(${example_name} ${version})
pico_set_program_url(${example_name} ${url})
pico_set_program_name(${example_name} ${example_name})
pico_set_program_url(${example_name} ${url})
pico_enable_stdio_usb(${example_name} 1)
pico_enable_stdio_uart(${example_name} 1)
pico_add_extra_outputs(${example_name})