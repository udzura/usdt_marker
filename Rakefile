require "bundler/gem_tasks"
require "rake/extensiontask"

task :build => :compile

Rake::ExtensionTask.new("usdt_marker") do |ext|
  ext.lib_dir = "lib/usdt_marker"
end

task :default => [:clobber, :compile, :spec]
