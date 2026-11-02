include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
add_library(vita_audio_decoder_interface INTERFACE)
add_library(VitaAudioDecoder::Interface ALIAS vita_audio_decoder_interface)
set_target_properties(vita_audio_decoder_interface PROPERTIES EXPORT_NAME Interface)
target_include_directories(vita_audio_decoder_interface INTERFACE
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
install(TARGETS vita_audio_decoder_interface EXPORT VitaAudioDecoderTargets)
install(EXPORT VitaAudioDecoderTargets NAMESPACE VitaAudioDecoder:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VitaAudioDecoder)
configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/../cmake/VitaAudioDecoderConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/VitaAudioDecoderConfig.cmake INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VitaAudioDecoder)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/VitaAudioDecoderConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VitaAudioDecoder)
install(FILES
 ${CMAKE_CURRENT_LIST_DIR}/../include/vita_audio_types.h
 ${CMAKE_CURRENT_LIST_DIR}/../include/vita_audio_playback.h
 ${CMAKE_CURRENT_LIST_DIR}/../include/vita_audio_gain.h
 ${CMAKE_CURRENT_LIST_DIR}/../include/vita_audio_formats.h
 DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
