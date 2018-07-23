%%%-------------------------------------------------------------------
%%% @author Joseph
%%% @copyright (C) 2018, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 22. Apr 2018 21:23
%%%-------------------------------------------------------------------
-module(pollution_tests).
-author("Joseph").

-include_lib("eunit/include/eunit.hrl").
-compile(export_all).

testCoords_test() ->
  {Date, _} = calendar:local_time(),
  {Y, M, D} = Date,
  Date2 = {Y, M, D+1},
  Date3 = {Y, M, D+2},
  Monitor0 = pollution:createMonitor(),
  Monitor1 = pollution:addStation(Monitor0, {1,1}, "a"),
  Monitor2 = pollution:addValue(Monitor1, {1,1}, Date, "PM10", 50),
  Monitor3 = pollution:addValue(Monitor2, {1,1}, Date, "PM2.5", 250),
  Monitor4 = pollution:addStation(Monitor3, {1,2}, "b"),
  Monitor5 = pollution:addValue(Monitor4, {1,2}, Date, "PM10", 100),
  Monitor6 = pollution:addValue(Monitor5, {1,2}, Date, "PM2.5", 200),
  Monitor7 = pollution:addValue(Monitor6, "a", Date2, "PM10", 20),
  Monitor = pollution:addValue(Monitor7, "a", Date3, "PM10", 20),
  ?assertEqual(pollution:getOneValue(Monitor, {1,1}, Date, "PM10"), 50),
  ?assertEqual(pollution:getOneValue(Monitor, "a", Date, "PM10"), 50),
  ?assertEqual(pollution:getOneValue(Monitor, {1,1}, Date, "PM2.5"), 250),
  ?assertEqual(pollution:getOneValue(Monitor, "a", Date, "PM2.5"), 250),
  ?assertEqual(pollution:getStationMean(Monitor, {1,1}, "PM10"), 30.0),
  ?assertEqual(pollution:getDailyMean(Monitor, Date, "PM2.5"), 225.0).

daily_test() ->
  M = pollution:createMonitor(),
  M1 = pollution:addStation(M, {1,1}, "a"),
  M2 = pollution:addStation(M1, {2,2}, "b"),
  Date = {1, 1, 1},
  Date2 = {2,2,2},
  Date3 = {3,3,3},
  M3 = pollution:addValue(M2, "a", Date, "PM10", 10),
  M4 = pollution:addValue(M3, "a", Date2, "PM10", 10),
  M5 = pollution:addValue(M4, "a", Date3, "PM10", 10),
  M6 = pollution:addValue(M5, "a", Date3, "PM2.5", 10),
  M7 = pollution:addValue(M6, "a", Date2, "PM2.5", 10),
  M8 = pollution:addValue(M7, "a", Date, "PM2.5", 10),
  ?assertEqual(pollution:getDailyAverageDataCount(M8, "a"), 2.0),
  ?assertEqual(pollution:getDailyAverageDataCount(M6, "a"), 1.33333333333333333333333333333).