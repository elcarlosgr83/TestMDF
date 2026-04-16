# astyle --options=astylerc.sh --suffix=none --recursive "*.c,*.cc,*.cpp,*.h,*.hpp"

# Brace Style Options:
# --------------------
# default brace style
# If no brace style is requested, the opening braces will not be
# changed and closing braces will be broken from the preceding line.

# Java style formatting/indenting.
# Attached braces.
#--style=otbs

# Tab Options:
# ------------
# default indent option
# If no indentation option is set, the default
# option of 4 spaces per indent will be used.

# Indent using #  spaces per indent. Not specifying # 
# will result in a default of 4 spaces per indent.
--indent=spaces=2

# Indent using tab characters, assuming that each
# indent is #  spaces long. Not specifying #  will result
# in a default assumption of 4 spaces per indent.
#--indent=tab=2

# Indent using tab characters, assuming that each
# indent is #  spaces long. Force tabs to be used in areas
# AStyle would prefer to use spaces.
#--indent=force-tab=2

# Allows the tab length to be set to a length that is different
# from the indent length. This may cause the indentation to be
# a mix of both spaces and tabs. This option sets the tab length.
#--indent=force-tab-x=2

# Brace Modify Options:
# ---------------------
# Attach braces to a namespace statement.
--attach-namespaces

# Attach braces to a class statement.
--attach-classes

# Attach braces to class inline function definitions.
--attach-inlines

# Attach braces to an extern "C" statement.
--attach-extern-c

# Attach closing while of do-while to the closing brace.
--attach-closing-while

# Indentation Options:
# --------------------
# Indent 'class' blocks so that the entire block is indented.
#--indent-classes

# Indent 'class' access modifiers, 'public:', 'protected:' or
# 'private:', one half indent. The rest of the class is not
# indented.
#--indent-modifiers

# Indent 'switch' blocks, so that the inner 'case XXX:'
# headers are indented in relation to the switch block.
--indent-switches

# Indent case blocks from the 'case XXX:' headers.
# Case statements not enclosed in blocks are NOT indented.
#--indent-cases

# Indent the contents of namespace blocks.
--indent-namespaces

# Indent, instead of align, continuation lines following lines
# that contain an opening paren '(' or an assignment '='.
#--indent-after-parens

# Indent continuation lines an additional #  indents.
# The valid values are 0 thru 4 indents.
# The default value is 1 indent.
#--indent-continuation=3

# Indent labels so that they appear one indent less than
# the current indentation level, rather than being
# flushed completely to the left (which is the default).
#--indent-labels

# Indent preprocessor blocks at brace level 0.
# Without this option the preprocessor block is not indented.
--indent-preproc-block

# Indent preprocessor conditional statements # if/# else/# endif
# to the same level as the source code.
#--indent-preproc-cond

# Indent multi-line preprocessor # define statements.
--indent-preproc-define

# Indent line comments that start in column one.
--indent-col1-comments

# Indent C++ lambda functions (experimental, broken for complex fct bodies)
--indent-lambda
#--lambda-indent

# Indent a minimal #  spaces in a continuous conditional
# belonging to a conditional header.
# The valid values are:
# 0 - no minimal indent.
# 1 - indent at least one additional indent.
# 2 - indent at least two additional indents.
# 3 - indent at least one-half an additional indent.
# The default value is 2, two additional indents.
#--min-conditional-indent=3


# Indent a maximal #  spaces in a continuation line,
# relative to the previous line.
# The minimum and default value is 40.
#--max-continuation-indent=40

# Padding Options:
# ----------------
# Insert empty lines around unrelated blocks, labels, classes, ...
--break-blocks

# Like --break-blocks, except also insert empty lines
# around closing headers (e.g. 'else', 'catch', ...).
#--break-blocks=all

# Insert space padding around operators.
--pad-oper

# Insert space padding after commas.
--pad-comma

# Insert space padding around parenthesis on both the outside
# and the inside.
--pad-paren

# Insert space padding around parenthesis on the outside only.
#--pad-paren-out

# Insert space padding around first parenthesis in a series on
# the outside only.
#--pad-first-paren-out

# Insert space padding around parenthesis on the inside only.
#--pad-paren-in

# Apply padding to empty pairs of parentheses; combine with other
# parenthesis padding options.
--pad-empty-paren

# Insert space padding after paren headers (e.g. 'if', 'for'...).
--pad-header

# Remove unnecessary space padding around parenthesis. This
# can be used in combination with the 'pad' options above.
#--unpad-paren

# Insert space padding around square brackets on both the outside
# and the inside (experimental).
--pad-brackets

# Remove unnecessary space padding around square brackets (experimental).
#--unpad-brackets

# Delete empty lines within a function or method.
# It will NOT delete lines added by the break-blocks options.
#--delete-empty-lines

# Fill empty lines with the white space of their
# previous lines.
#--fill-empty-lines

# Remove superfluous empty lines exceeding the given number (experimental).
--squeeze-lines=2

# Remove superfluous whitespace (experimental).
--squeeze-ws

# Attach a pointer or reference operator (*, &, or ^) to either
# the operator type (left), middle, or operator name (right).
# To align the reference separately use --align-reference.
--align-pointer=type
#--align-pointer=middle
#--align-pointer=name

# Attach a reference operator (&) to either
# the operator type (left), middle, or operator name (right).
# If not set, follow pointer alignment.
#--align-reference=none
--align-reference=type
#--align-reference=middle
#--align-reference=name

# Formatting Options:
# -------------------

# Break braces before closing headers (e.g. 'else', 'catch', ...).
# Use with --style=java, --style=kr, --style=stroustrup,
#--style=linux
#--break-closing-braces

# Break 'else if()' statements into two different lines.
#--break-elseifs

# Break one line headers (e.g. 'if', 'while', 'else', ...) from a
# statement residing on the same line.
--break-one-line-headers

# Add braces to unbraced one line conditional statements.
--add-braces

# Add one line braces to unbraced one line conditional
# statements.
--add-one-line-braces

# Remove braces from a braced one line conditional statements.
#--remove-braces


# Break the return type from the function name. Options are
# for the function definitions and the function declarations.
#--break-return-type
#--break-return-type-decl

# Attach the return type to the function name. Options are
# for the function definitions and the function declarations.
--attach-return-type
#--attach-return-type-decl

# Don't break blocks residing completely on one line.
#--keep-one-line-blocks

# Don't break lines containing multiple statements into
# multiple single-statement lines.
#--keep-one-line-statements

# Convert tabs to the appropriate number of spaces.
--convert-tabs

# Close ending angle brackets on template definitions.
--close-templates

# Remove the leading '*' prefix on multi-line comments and
# indent the comment text one indent.
#--remove-comment-prefix

# max-code-length=#  will break the line if it exceeds more than
# #  characters. The valid values are 50 thru 200.
# If the line contains logical conditionals they will be placed
# first on the new line. The option break-after-logical will
# cause the logical conditional to be placed last on the
# previous line.
--max-code-length=80
#--break-after-logical

# Indent a C or C++ source file (this is the default).
--mode=c

# Indent a Java source file.
#--mode=java

# Indent a C#  source file.
#--mode=cs

# Indent an Objective-C source file.
#--mode=objc

# Indent a JavaScript source file (experimental).
#--mode=js

# Objective-C Options:
# --------------------
# Insert space padding after the '-' or '+' Objective-C
# method prefix.
#--pad-method-prefix

# Remove all space padding after the '-' or '+' Objective-C
# method prefix.
#--unpad-method-prefix

# Insert space padding after the Objective-C return type.
#--pad-return-type

# Remove all space padding after the Objective-C return type.
#--unpad-return-type

# Insert space padding after the Objective-C param type.
#--pad-param-type

# Remove all space padding after the Objective-C param type.
#--unpad-param-type

# Align the colons in an Objective-C method definition.
#--align-method-colon

# Add or remove space padding before or after the colons in an
# Objective-C method call.
#--pad-method-colon=none
#--pad-method-colon=all
#--pad-method-colon=after
#--pad-method-colon=before

# Other Options:
# --------------
# Append the suffix # # # #  instead of '.orig' to original filename.
#--suffix=# # # # 

# Do not retain a backup of the original file.
--suffix=none

# Process subdirectories recursively.
#--recursive "*.cpp,*.hpp"

# Perform a trial run with no changes made to check for formatting.
#--dry-run

# Specify a file or directory # # # #  to be excluded from processing.
#--exclude=# # # # 

# Allow processing to continue if there are errors in the exclude=# # # # 
# options. It will display the unmatched excludes.
#--ignore-exclude-errors

# Allow processing to continue if there are errors in the exclude=# # # # 
# options. It will NOT display the unmatched excludes.
#--ignore-exclude-errors-x

# Print errors and help information to standard-output rather than
# to standard-error.
#--errors-to-stdout

# Preserve the original file's date and time modified. The time
#  modified will be changed a few micro seconds to force a compile.
#--preserve-date

# Verbose mode. Extra informational messages will be displayed.
#--verbose

# Formatted display mode. Display only the files that have been
# formatted.
#--formatted

# Quiet mode. Suppress all output except error messages.
#--quiet

# Force use of the specified line end style. Valid options
# are windows (CRLF), linux (LF), and macold (CR).
#--lineend=windows
#--lineend=linux
#--lineend=macold
