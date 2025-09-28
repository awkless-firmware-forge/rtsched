#!/usr/bin/env -S gawk -f
# SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

BEGIN {
  print_usage()
  init_theme()
  FS = "(:.*##|=)"
}

# options:: <var> ?= <default>
/^[a-zA-Z_\-]+\s=.*/ {
  printf("  %s%-20s%s (default: %s%s%s)%s\n",
    fg_option, $1, fg_comment, fg_value, $2, fg_comment, c_reset)
}

# headings:: ##! <subject>
/^##!/ {
  printf("\n%s%s:%s\n", fg_heading, substr($0, 5), c_reset)
}

## targets:: <target>: ## <description>
/^[a-zA-Z_0-9\-\/\.]+:.*?##/ {
  desc = gensub(/(\$[a-zA-Z_\-\(\)]+)/, sprintf("%s\\1%s", fg_value, fg_comment), "g", $2)
  printf("  %s%-20s%s%s%s\n", fg_target, $1, fg_comment, desc, c_reset)
}

function print_usage() {
	printf("%sUsage:%s make%s", fg_heading, fg_binary, c_reset)
	printf(" %s[%soption%s=value]...%s", fg_value, fg_option, fg_value, c_reset)
	printf(" %s[%scommand%s]%s", fg_value, fg_target, fg_value, c_reset)
}

function init_theme() {
  c_reset = "\33[0m"
  c_bold = "\33[1m"
  c_green = "\33[32m"
  c_blue = "\33[34m"
  c_cyan = "\33[36m"
  c_white = "\33[37m"

  fg_binary = sprintf("%s%s%s", c_reset, c_bold, c_cyan)
  fg_heading = sprintf("%s%s%s",c_reset, c_bold, c_green)
  fg_target = sprintf("%s%s%s", c_reset, c_bold, c_cyan)
  fg_option = sprintf("%s%s%s", c_reset, c_bold, c_cyan)
  fg_value = sprintf("%s%s", c_reset, c_cyan)
  fg_comment = sprintf("%s", c_reset)
}
