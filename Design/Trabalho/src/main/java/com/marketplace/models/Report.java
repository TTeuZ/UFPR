package com.marketplace.models;

import com.marketplace.enums.ReasonType;

public class Report {
    private ReasonType reason;
    private String description;

    public Report(ReasonType reason, String description) {
        this.reason = reason;
        this.description = description;
    }

    public static String parseReason(ReasonType reason) {
        switch (reason) {
            case SCAM:
                return "Golpe";
            case ABUSIVE_SELLER:
                return "Vendedor Abusivo";
            default:
                return "";
        }
    }
}