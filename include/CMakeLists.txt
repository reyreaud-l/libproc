set(LIB_INCLUDES
  error.hh
  helper.hh
  mstat.hh
  periodic_watcher.hh
  plib.hh
  process.hh
  pstat.hh
  watcher.hh
)

install(FILES ${LIB_INCLUDES} DESTINATION include/plib)
