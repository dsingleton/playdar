ADD_LIBRARY( boffin SHARED
             boffin.cpp
             BoffinDb.cpp
             ResultSet.cpp
             SimilarArtists.cpp
             parser/parser.cpp 
             RqlOpProcessor.cpp 
             ${DEPS}/sqlite3pp-read-only/sqlite3pp.cpp
             ${DEPS}/json_spirit_v3.00/json_spirit/json_spirit_writer.cpp             
             )

SET_TARGET_PROPERTIES( boffin PROPERTIES
                       PREFIX ""
                       SUFFIX ".resolver"
                       CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PLAYDAR_DIR}/plugins" )

TARGET_LINK_LIBRARIES(boffin
                      ${Boost_LIBRARIES}
                      ${PLAYDAR_PLUGIN_LDFLAGS}
                      ${SQLITE3_LIBRARIES}
                      ${CURL_LIBRARIES}
					  )
                    
ADD_EXECUTABLE( tagger
                Tagger.cpp
                BoffinDb.cpp
				${CURL_INCLUDE_DIR}
                ${DEPS}/sqlite3pp-read-only/sqlite3pp.cpp )

TARGET_LINK_LIBRARIES( tagger
                       ${SQLITE3_LIBRARIES}
                       ${Boost_LIBRARIES} 
					   ${CURL_LIBRARIES} )
					   
					   
