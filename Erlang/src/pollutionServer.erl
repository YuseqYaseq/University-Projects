%%%-------------------------------------------------------------------
%%% @author Joseph
%%% @copyright (C) 2018, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 24. Apr 2018 12:40
%%%-------------------------------------------------------------------
-module(pollutionServer).
-author("Joseph").

%% API
-export([start/0, stop/0, init/1]).

init(Monitor) ->
  loop(Monitor).

start() ->
  register(server, spawn(pollutionServer, init, [pollution:createMonitor()])).

stop() ->
  unregister(server).

loop(Monitor) ->
  receive
    {PID, addStation, [{X, Y}, Name]} ->
      try pollution:addStation(Monitor, {X, Y}, Name) of
        M ->
          PID ! ok,
          loop(M)
      catch
          throw:station_already_exists ->
            PID ! station_already_exists,
            loop(Monitor)
      end;
    {PID, addValue, [{X,Y}, Date, Type, Value]} ->
      try pollution:addValue(Monitor, {X,Y}, Date, Type, Value) of
        M ->
          PID ! ok,
          loop(M)
      catch
        throw:value_already_exists ->
          PID ! value_already_exists,
          loop(Monitor)
      end;
    {PID, addValue, [Name, Date, Type, Value]} ->
      try pollution:addValue(Monitor, Name, Date, Type, Value) of
        M ->
          PID ! ok,
          loop(M)
      catch
        throw:value_already_exists ->
          PID ! value_already_exists,
          loop(Monitor)
      end;
    {PID, removeValue, [{X,Y}, Date, Type]} ->
      try pollution:removeValue(Monitor, {X,Y}, Date, Type) of
        M ->
          PID ! ok,
          loop(M)
      catch
        throw:value_already_exists ->
          PID ! value_already_exists,
          loop(Monitor)
      end;
    {PID, removeValue, [Name, Date, Type]} ->
      try pollution:removeValue(Monitor, Name, Date, Type) of
        M ->
          PID ! ok,
          loop(M)
      catch
        throw:value_already_exists ->
          PID ! value_already_exists,
          loop(Monitor)
      end;
    {PID, getOneValue, [{X, Y}, Date, Type]} ->
      PID ! pollution:getOneValue(Monitor, {X,Y}, Date, Type),
      loop(Monitor);
    {PID, getOneValue, [Name, Date, Type]} ->
      PID ! pollution:getOneValue(Monitor, Name, Date, Type),
      loop(Monitor);
    {PID, getStationMean, [{X,Y}, Type]} ->
      PID ! pollution:getStationMean(Monitor, {X,Y}, Type),
      loop(Monitor);
    {PID, getStationMean, [Name, Type]} ->
      PID ! pollution:getStationMean(Monitor, Name, Type),
      loop(Monitor);
    {PID, getDailyMean, [Date, Type]} ->
      PID ! pollution:getDailyMean(Monitor, Date, Type),
      loop(Monitor);
    {PID, getDailyAverageDataCount, Name} ->
      PID ! pollution:getDailyAverageDataCount(Monitor, Name),
      loop(Monitor)
  end.