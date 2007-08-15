.First.lib <- function(lib, pkg)
{  library.dynam("pga", pkg, lib)
    cat("pga 0.1-1 loaded\n")
}
