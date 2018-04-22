%%%-------------------------------------------------------------------
%%% @author Joseph
%%% @copyright (C) 2018, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 22. Apr 2018 14:58
%%%-------------------------------------------------------------------
-module(pollution).
-author("Joseph").

%% API
-export([createMonitor/0, addStation/3, addValue/5, removeValue/4, getOneValue/4, getStationMean/3, getDailyMean/3]).

-record(coord, {x, y}).
-record(monitor, {coords = #{}, names = #{}}).
%%-record(station, {values=#{}}).

createMonitor() -> #monitor{}.

addStation(#monitor{coords = C, names = N}, {X, Y}, Name) ->
  case {maps:is_key(#coord{x = X, y = Y}, C), maps:is_key(Name, N)} of
    {false, false} -> #monitor{coords = maps:put(#coord{x = X, y = Y}, Name, C), names = maps:put(Name, #{}, N)};
    _ -> throw("Station already exists!")
  end.

addValue(#monitor{coords = C, names = N}, {X, Y}, Date, Type, Value) ->
  addValue(#monitor{coords = C, names = N},
           maps:get(#coord{x = X, y = Y}, C), Date, Type, Value);
addValue(#monitor{coords = C, names = N}, Name, Date, Type, Value) ->
  case maps:is_key({Type, Date}, maps:get(Name, N)) of
    false -> #monitor{coords = C, names = maps:put(Name, maps:put({Type, Date}, Value, maps:get(Name, N)), N)};
    _ -> throw("Value already exists!")
  end.

removeValue(#monitor{coords = C, names = N}, {X, Y}, Date, Type) ->
  removeValue(#monitor{coords = C, names = N},
    maps:get(#coord{x = X, y = Y}, C), Date, Type);
removeValue(#monitor{coords = C, names = N}, Name, Date, Type) ->
  case maps:is_key({Type, Date}, maps:get(Name, N)) of
    true -> #monitor{coords = C, names = maps:put(Name, maps:remove({Type, Date}, maps:get(Name, N)), N)};
    _ -> throw("There is no such value!")
  end.

getOneValue(#monitor{coords = C, names = N}, {X, Y}, Date, Type) ->
  getOneValue(#monitor{coords = C, names = N},
    maps:get(#coord{x = X, y = Y}, C), Date, Type);
getOneValue(#monitor{names = N}, Name, Date, Type) ->
  maps:get({Type, Date}, maps:get(Name, N)).

getStationMean(#monitor{coords = C, names = N}, {X, Y}, Type) ->
  getStationMean(#monitor{coords = C, names = N},
    maps:get(#coord{x = X, y = Y}, C), Type);
getStationMean(#monitor{names = N}, Name, Type) ->
  {X, Y} = maps:fold(fun({T, _}, V, {Acc1, Acc2}) -> case T of
                                              Type -> {V + Acc1, 1+Acc2};
                                              _ -> {Acc1, Acc2}
                                            end end,
            {0, 0}, maps:get(Name, N)),
  case Y of
    0 -> 0;
    _ -> X/Y
  end.

getDailyMean(#monitor{names = N}, Date, Type) ->
  {X, Y} = maps:fold(fun(_, V, {Sum, Num}) ->
    case maps:is_key({Type, Date}, V) of
      true -> {maps:get({Type, Date}, V) + Sum, 1 + Num};
      _ -> {Sum, Num}
    end end, {0, 0}, N),
  case Y of
    0 -> 0;
    _ -> X/Y
  end.