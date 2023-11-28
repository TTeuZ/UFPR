package com.marketplace.controllers;

import com.marketplace.enums.ReasonType;
import com.marketplace.models.User;

public class UserController {
    public void report(User user, ReasonType reason, String description) {
        user.addReport(reason, description);
    }
}
