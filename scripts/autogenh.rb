N_ARGS = 12

puts "#ifndef __MINITEST_AUTOGENERATED_H__"
puts "#define __MINITEST_AUTOGENERATED_H__ 1"

puts "\n//\n// This file was autogenerated. Do not modify this file.\n//\n\n"

##
# sizeof args
##
puts "#define mt_sizeof_va_args(...) mt_sizeof_va_args_definition(__VA_ARGS__)"
puts "#define mt_sizeof_va_args_definition(n, ...) mt_sizeof_va_args_##n(__VA_ARGS__)"

##
# Helpers/Roots
##
puts "#define mt_mock_argtype_string(v) #v"
puts "#define mt_mock_function_args_0(...)   char* args[] = {}"

puts "#define mt_va_nargs(...) mt_va_nargs_definition(__VA_ARGS__, #{N_ARGS.downto(1).map{|n|n}.join(',')})"
puts "#define mt_va_nargs_definition(#{1.upto(N_ARGS).map{ |j| '_'+j.to_s }.join(',')}, N, ...) N"

puts "#define mt_spy_args(...) ( mt_spy_args_definition(__VA_ARGS__) )"
puts "#define mt_spy_args_definition(n, ...) mt_spy_args_##n(__VA_ARGS__)"

puts "#define mt_spy_arg_ptrs(...) ( mt_spy_arg_ptrs_(mt_va_nargs(__VA_ARGS__), __VA_ARGS__) )"
puts "#define mt_spy_arg_ptrs_(...)  mt_spy_arg_ptrs_definition(__VA_ARGS__)"
puts "#define mt_spy_arg_ptrs_definition(n, ...) mt_spy_arg_ptrs_##n(__VA_ARGS__)"

1.upto(N_ARGS).each do |i|

  puts "#define mt_sizeof_va_args_#{i}(#{1.upto(i).map{ |j| 'n'+j.to_s }.join(',')}) (size_t[]){#{1.upto(i).map{ |j| 'sizeof(n'+j.to_s+')' }.join(',')}}"

  puts "#define mt_mock_function_args_#{i}(#{1.upto(i).map{ |j| 'n'+j.to_s }.join(',')}) char* args[] = { #{1.upto(i).map{ |j| 'mt_mock_argtype_string(n'+j.to_s+')' }.join(',')} }"

  puts "#define mt_spy_args_#{i}(#{1.upto(i).map{ |j| 'n'+j.to_s }.join(',')}) #{1.upto(i).map{ |j| 'n'+j.to_s+'*' }.join(',')}"

  puts "#define mt_spy_arg_ptrs_#{i}(#{1.upto(i).map{ |j| 'n'+j.to_s }.join(',')}) #{1.upto(i).map{ |j| '&n'+j.to_s }.join(',')}"
end

puts "#endif"