// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: exchange.proto

package exchange.proto_out;

public interface CurrencyArgumentsOrBuilder extends
    // @@protoc_insertion_point(interface_extends:CurrencyArguments)
    com.google.protobuf.MessageOrBuilder {

  /**
   * <code>.CurrencyType ReferenceCurrency = 1;</code>
   */
  int getReferenceCurrencyValue();
  /**
   * <code>.CurrencyType ReferenceCurrency = 1;</code>
   */
  exchange.proto_out.CurrencyType getReferenceCurrency();

  /**
   * <code>repeated .CurrencyType Currencies = 2;</code>
   */
  java.util.List<exchange.proto_out.CurrencyType> getCurrenciesList();
  /**
   * <code>repeated .CurrencyType Currencies = 2;</code>
   */
  int getCurrenciesCount();
  /**
   * <code>repeated .CurrencyType Currencies = 2;</code>
   */
  exchange.proto_out.CurrencyType getCurrencies(int index);
  /**
   * <code>repeated .CurrencyType Currencies = 2;</code>
   */
  java.util.List<java.lang.Integer>
  getCurrenciesValueList();
  /**
   * <code>repeated .CurrencyType Currencies = 2;</code>
   */
  int getCurrenciesValue(int index);
}
