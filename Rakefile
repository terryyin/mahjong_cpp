require 'rake'
require 'rubygems'
require "jshintrb/jshinttask"

task :default => [:test_everything]

task :test_everything do   
   	Rake::Task['run_game_server_daemon'].invoke
   	begin
    	  Rake::Task['jasmine:ci'].invoke
    ensure
      Rake::Task['stop_game_server_daemon'].invoke
    end
end

desc "Startup game as a daemon"
task :run_game_server_daemon do
  sh "./mahjong&"
end

desc "Kill game"
task :stop_game_server_daemon do
  sh "pkill mahjong"
end

begin
  require 'jasmine'
  load 'jasmine/tasks/jasmine.rake'
rescue LoadError
  task :jasmine do
    abort "Jasmine is not available. In order to run jasmine, you must: (sudo) gem install jasmine"
  end
end

Jshintrb::JshintTask.new :jshint do |t|
  t.pattern = 'htdocs/mj.js'
  t.options = :defaults
end

