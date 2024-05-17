# soren-lang

## soren grammar

_expr_      →   _term_ _expr'_

_expr'_     →   + _term_ _expr'_ | - _term_ _expr'_ | ϵ

_term_      →   _unary_ _term'_ 

_term'_     →   * _unary_ _term'_ | / _unary_ _term'_ | ϵ

_unary_     →   - _factor_ | _factor_

_factor_    →   ( _expr_ ) | **[0-9]**
