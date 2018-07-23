
package com.agh.console.nbp.domain;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class CurrencyRate implements Comparable<CurrencyRate> {

    @SerializedName("no")
    @Expose
    private String no;
    @SerializedName("effectiveDate")
    @Expose
    private String effectiveDate;
    @SerializedName("mid")
    @Expose
    private Double mid;
    @SerializedName("bid")
    @Expose
    private Double bid;
    @SerializedName("ask")
    @Expose
    private Double ask;
    @SerializedName("code")
    @Expose
    private String code;

    public String getNo() {
        return no;
    }

    public void setNo(String no) {
        this.no = no;
    }

    public String getEffectiveDate() {
        return effectiveDate;
    }

    public void setEffectiveDate(String effectiveDate) {
        this.effectiveDate = effectiveDate;
    }

    public Double getMid() {
        return mid;
    }

    public void setMid(Double mid) {
        this.mid = mid;
    }

    public Double getBid() {
        return bid;
    }

    public void setBid(Double bid) {
        this.bid = bid;
    }

    public Double getAsk() {
        return ask;
    }

    public void setAsk(Double ask) {
        this.ask = ask;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }


    @Override
    public String toString() {
        return "CurrencyRate{" +
                "no='" + no + '\'' +
                ", effectiveDate='" + effectiveDate + '\'' +
                ", mid=" + mid +
                ", bid=" + bid +
                ", ask=" + ask +
                ", code='" + code + '\'' +
                '}';
    }

/*    public int compareTo(CurrencyRate obj1, CurrencyRate obj2) {
        return obj1.getAsk() - obj1.getBid();
    }*/

    public int compareTo(CurrencyRate o) {
        double delta = (getAsk() - getBid()) - (o.getAsk() - o.getBid());
        //if ((obj1.getAsk() - obj1.getBid()) < (obj2.getAsk() - obj2.getBid())) return -1;
        //if ((obj1.getAsk() - obj1.getBid()) > (obj2.getAsk() - obj2.getBid())) return 1;

        //double delta= p1.getY() - p2.getY();
        if(delta > 0) return 1;
        if(delta < 0) return -1;
        return 0;
        /*return (getAsk() - getBid()) - (o.getAsk() - o.getBid());*/
    }

/*    public class ComparatorClass implements Comparator<CurrencyRate> {
        public int compare(CurrencyRate obj1, CurrencyRate obj2) {
            double delta = (obj1.getAsk() - obj1.getBid()) - (obj2.getAsk() - obj2.getBid());
            //if ((obj1.getAsk() - obj1.getBid()) < (obj2.getAsk() - obj2.getBid())) return -1;
            //if ((obj1.getAsk() - obj1.getBid()) > (obj2.getAsk() - obj2.getBid())) return 1;

            //double delta= p1.getY() - p2.getY();
            if(delta > 0) return 1;
            if(delta < 0) return -1;
            return 0;
        }
    }*/
}
