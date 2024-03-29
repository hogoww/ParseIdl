specification
	:	import_decl* definition+
	;
	
definition
	:	type_decl ';'
	|	const_decl ';'
	|	except_decl ';'
	|	interface_or_forward_decl ';'
	|	module ';'
	|	value ';'
	|	type_id_decl ';'
	|	type_prefix_decl ';'
	|	event ';'
	|	component ';'
	|	home_decl ';'
	;
	
module
	:	'module' ID '{' definition+ '}'
	;
	
interface_or_forward_decl
	:	interface_decl
	|	forward_decl
	;
	
interface_decl
	:	interface_header '{' interface_body '}'
	;
	
forward_decl
	:	( 'abstract' | 'local' )? 'interface' ID
	;
	
interface_header
	:	( 'abstract' | 'local' )? 'interface' ID
		( interface_inheritance_spec )?
	;
	
interface_body
	:	export*
	;
	
export
	:	type_decl ';'
	|	const_decl ';'
	|	except_decl ';'
	|	attr_decl ';'
	|	op_decl ';'
	|	type_id_decl ';'
	|	type_prefix_decl ';'
	;
	
interface_inheritance_spec
	:	':' interface_name
		( ',' interface_name )*
	;
	
interface_name
	:	scoped_name
	;
	
scoped_name
	:	( '::' )? ID ( '::' ID )*
	;
	
value
	:	( value_decl | value_abs_decl | value_box_decl | value_forward_decl )
	;
	
value_forward_decl
	:	( 'abstract' )? 'valuetype' ID
	;
	
value_box_decl
	:	'valuetype' ID type_spec
	;
	
value_abs_decl
	:	'abstract' 'valuetype' ID
		( value_inheritance_spec )?
		'{' export* '}'
	;
	
value_decl
	:	value_header '{'  value_element* '}'
	;
	
value_header
	:	('custom' )? 'valuetype' ID
		( value_inheritance_spec )?
	;
	
value_inheritance_spec
	:	( ':' ( 'truncatable' )? value_name
		( ',' value_name )* )?
		( 'supports' interface_name
		( ',' interface_name )* )?
	;
	
value_name
	:	scoped_name
	;
	
value_element
	:	export |  state_member | init_decl
	;
	
state_member
	:	( 'public' | 'private' )
		type_spec declarators ';'
	;
	
init_decl
	:	'factory' ID
		'(' ( init_param_decls )? ')'
		( raises_expr )? ';'
	;
	
init_param_decls
	:	init_param_decl ( ',' init_param_decl )*
	;
	
init_param_decl
	:	init_param_attribute param_type_spec
		simple_declarator
	;
	
init_param_attribute
	:	'in'
	;
	
const_decl
	:	'const' const_type
		ID '=' const_exp
	;
	
const_type
	:	integer_type
	|	char_type
	|	wide_char_type
	|	boolean_type
	|	floating_pt_type
	|	string_type
	|	wide_string_type
	|	fixed_pt_const_type
	|	scoped_name
	|	octet_type
	;
	
const_exp
	:	or_expr
	;
	
or_expr
	:	xor_expr ( '|' xor_expr )*
	;
	
xor_expr
	:	and_expr ( '^' and_expr )*
	;
	
and_expr
	:	shift_expr ( '&' shift_expr )*
	;
	
shift_expr
	:	add_expr ( ( '>>' | '<<' ) add_expr )*
	;
	
add_expr
	:	mult_expr ( ( '+' | '-' ) mult_expr )*
	;
	
mult_expr
	:	unary_expr ( ( '*' | '/' | '%' ) unary_expr )*
	;
	
unary_expr
	:	unary_operator primary_expr
	|	primary_expr
	;
	
unary_operator
	:	'-'
	|	'+'
	|	'~'
	;
	
primary_expr
	:	scoped_name
	|	literal
	|	'(' const_exp ')'
	;
	
literal
	:	INTEGER_LITERAL
	|	STRLIT
	|	WIDE_STRING_LITERAL
	|	CHARLIT
	|	WIDE_CHARACTER_LITERAL
	|	FIXED_PT_LITERAL
	|	FLOATING_PT_LITERAL
	|	BOOLEAN_LITERAL
	;
	
positive_int_const
	:	const_exp
	;
	
type_decl
	:	'typedef' type_declarator
	|	struct_type
	|	union_type
	|	enum_type
	|	'native' simple_declarator
	|	constr_forward_decl
	;
	
type_declarator
	:	type_spec declarators
	;
	
type_spec
	:	simple_type_spec
	|	constr_type_spec
	;
	
simple_type_spec
	:	base_type_spec
	|	template_type_spec
	|	scoped_name
	;
	
base_type_spec
	:	floating_pt_type
	|	integer_type
	|	char_type
	|	wide_char_type
	|	boolean_type
	|	octet_type
	|	any_type
	|	object_type
	|	value_base_type
	;
	
template_type_spec
	:	sequence_type
	|	string_type
	|	wide_string_type
	|	fixed_pt_type
	;
	
constr_type_spec
	:	struct_type
	|	union_type
	|	enum_type
	;
	
declarators
	:	declarator ( ',' declarator )*
	;
	
declarator
	:	simple_declarator
	|	complex_declarator
	;
	
simple_declarator
	:	ID
	;
	
complex_declarator
	:	array_declarator
	;
	
floating_pt_type
	:	'float'
	|	'double'
	|	'long' 'double'
	;
	
integer_type
	:	signed_int
	|	unsigned_int
	;
	
signed_int
	:	signed_short_int
	|	signed_long_int
	|	signed_longlong_int
	;
	
signed_short_int
	:	'short'
	;
	
signed_long_int
	:	'long'
	;
	
signed_longlong_int
	:	'long' 'long'
	;
	
unsigned_int
	:	unsigned_short_int
	|	unsigned_long_int
	|	unsigned_longlong_int
	;
	
unsigned_short_int
	:	'unsigned' 'short'
	;
	
unsigned_long_int
	:	'unsigned' 'long'
	;
	
unsigned_longlong_int
	:	'unsigned' 'long' 'long'
	;
	
char_type
	:	'char'
	;
	
wide_char_type
	:	'wchar'
	;
	
boolean_type
	:	'boolean'
	;
	
octet_type
	:	'octet'
	;
	
any_type
	:	'any'
	;
	
object_type
	:	'Object'
	;
	
struct_type
	:	'struct' ID '{' member_list '}'
	;
	
member_list
	:	member+
	;
	
member
	:	type_spec declarators ';'
	;
	
union_type
	:	'union' ID
		'switch' '(' switch_type_spec ')'
		'{' switch_body '}'
	;
	
switch_type_spec
	:	integer_type
	|	char_type
	|	boolean_type
	|	enum_type
	|	scoped_name
	;
	
switch_body
	:	case_stmt+
	;
	
case_stmt
	:	case_label+ element_spec ';'
	;
	
case_label
	:	'case' const_exp ':'
	|	'default' ':'
	;
	
element_spec
	:	type_spec declarator
	;
	
enum_type
	:	'enum' ID
		'{' enumerator ( ',' enumerator )* '}'
	;
	
enumerator
	:	ID
	;
	
sequence_type
	:	'sequence' '<' simple_type_spec ',' positive_int_const '>'
	|	'sequence' '<' simple_type_spec '>'
	;
	
string_type
	:	'string' '<' positive_int_const '>'
	|	'string'
	;
	
wide_string_type
	:	'wstring' '<' positive_int_const '>'
	|	'wstring'
	;
	
array_declarator
	:	ID fixed_array_size+
	;
	
fixed_array_size
	:	'[' positive_int_const ']'
	;
	
attr_decl
	:	readonly_attr_spec
	|	attr_spec
	;
	
except_decl
	:	'exception' ID '{' member* '}'
	;
	
op_decl
	:	( op_attribute )? op_type_spec
		ID parameter_decls
		( raises_expr )? ( context_expr )?
	;
	
op_attribute
	:	'oneway'
	;
	
op_type_spec
	:	param_type_spec
	|	'void'
	;
	
parameter_decls
	:	'(' param_decl ( ',' param_decl )* ')'
	|	'(' ')'
	;
	
param_decl
	:	param_attribute param_type_spec
		simple_declarator
	;
	
param_attribute
	:	'in'
	|	'out'
	|	'inout'
	;
	
raises_expr
	:	'raises' '(' scoped_name
		( ',' scoped_name )* ')'
	;
	
context_expr
	:	'context' '(' STRLIT
		( ',' STRLIT )* ')'
	;
	
param_type_spec
	:	base_type_spec
	|	string_type
	|	wide_string_type
	|	scoped_name
	;
	
fixed_pt_type
	:	'fixed' '<' positive_int_const ','
		positive_int_const '>'
	;
	
fixed_pt_const_type
	:	'fixed'
	;
	
value_base_type
	:	'ValueBase'
	;
	
constr_forward_decl
	:	'struct' ID
	|	'union' ID
	;
	
import_decl
	:	'import' imported_scope ';'
	;
	
imported_scope
	:	scoped_name | STRLIT
	;
	
type_id_decl
	:	'typeid' scoped_name STRLIT
	;
	
type_prefix_decl
	:	'typeprefix' scoped_name STRLIT
	;
	
readonly_attr_spec
	:	'readonly' 'attribute' param_type_spec
		readonly_attr_declarator
	;
	
readonly_attr_declarator
	:	simple_declarator raises_expr
	|	simple_declarator
		( ',' simple_declarator )*
	;
	
attr_spec
	:	'attribute' param_type_spec
		attr_declarator
	;
	
attr_declarator
	:	simple_declarator attr_raises_expr
	|	simple_declarator
		( ',' simple_declarator )*
	;
	
attr_raises_expr
	:	get_excep_expr ( set_excep_expr )?
	|	set_excep_expr
	;
	
get_excep_expr
	:	'getraises' exception_list
	;
	
set_excep_expr
	:	'setraises' exception_list
	;
	
exception_list
	:	'(' scoped_name
		( ',' scoped_name )* ')'
	;
	
component
	:	component_decl
	|	component_forward_decl
	;
	
component_forward_decl
	:	'component' ID
	;
	
component_decl
	:	component_header
		'{' component_body '}'
	;
	
component_header
	:	'component' ID
		( component_inheritance_spec )?
		( supported_interface_spec )?
	;
	
supported_interface_spec
	:	'supports' scoped_name
		( ',' scoped_name )*
	;
	
component_inheritance_spec
	:	':' scoped_name
	;
	
component_body
	:	component_export*
	;
	
component_export
	:	provides_decl ';'
	|	uses_decl ';'
	|	emits_decl ';'
	|	publishes_decl ';'
	|	consumes_decl ';'
	|	attr_decl ';'
	;
	
provides_decl
	:	'provides' interface_type ID
	;
	
interface_type
	:	scoped_name
	|	'Object'
	;
	
uses_decl
	:	'uses' ( 'multiple' )?
		interface_type ID
	;
	
emits_decl
	:	'emits' scoped_name ID
	;
	
publishes_decl
	:	'publishes' scoped_name ID
	;
	
consumes_decl
	:	'consumes' scoped_name ID
	;
	
home_decl
	:	home_header home_body
	;
	
home_header
	:	'home' ID
		( home_inheritance_spec )?
		( supported_interface_spec )?
		'manages' scoped_name
		( primary_key_spec )?
	;
	
home_inheritance_spec
	:	':' scoped_name
	;
	
primary_key_spec
	:	'primarykey' scoped_name
	;
	
home_body
	:	'{' home_export* '}'
	;
	
home_export
	:	export
	|	factory_decl ';'
	|	finder_decl ';'
	;
	
factory_decl
	:	'factory' ID
		'(' ( init_param_decls )? ')'
		( raises_expr )?
	;
	
finder_decl
	:	'finder' ID
		'(' ( init_param_decls )? ')'
		( raises_expr )?
	;
	
event
	:	( event_decl | event_abs_decl |
		event_forward_decl)
	;
	
event_forward_decl
	:	( 'abstract' )? 'eventtype' ID
	;
	
event_abs_decl
	:	'abstract' 'eventtype' ID
		( value_inheritance_spec )?
		'{' export* '}'
	;
	
event_decl
	:	event_header '{' value_element* '}'
	;
	
event_header
	:	( 'custom' )? 'eventtype'
		ID ( value_inheritance_spec )?
	;
	
	
INTEGER_LITERAL : DIGIT+ INTEGER_TYPE_SUFFIX? ;

INTEGER_TYPE_SUFFIX : ('l'|'L') ;

FLOATING_PT_LITERAL
	:	DIGIT+ '.' DIGIT* EXPONENT? FLOAT_TYPE_SUFFIX?
	|	'.' DIGIT+ EXPONENT? FLOAT_TYPE_SUFFIX?
	|	DIGIT+ EXPONENT FLOAT_TYPE_SUFFIX?
	|	DIGIT+ EXPONENT? FLOAT_TYPE_SUFFIX
	;
	
FIXED_PT_LITERAL
	:	FLOATING_PT_LITERAL
	;

EXPONENT : ('e'|'E') ('+'|'-')? DIGIT+ ;

FLOAT_TYPE_SUFFIX : ('f'|'F'|'d'|'D') ;

WIDE_CHARACTER_LITERAL
	:	'L' CHARLIT
	;

WIDE_STRING_LITERAL
	:	'L' STRLIT
	;

BOOLEAN_LITERAL
	:	'TRUE'
	|	'FALSE'
	;
