# soren-lang

## soren grammar

_expr_      →   _term_ _expr'_

_expr'_     →   __+__ _term_ _expr'_ | __-__ _term_ _expr'_ | ϵ

_term_      →   _factor_ _term'_ 

_term'_     →   __*__ _factor_ _term'_ | __/__ _factor_ _term'_ | ϵ

_factor_    →   __(__ _expr_ __)__ | [ - ]__[0-9]__
