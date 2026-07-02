package com.portfolio.controller;

import com.portfolio.model.Project;
import com.portfolio.model.Expertise;
import com.portfolio.model.ContactMessage;
import com.portfolio.service.PortfolioService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Controller
public class PortfolioController {

    @Autowired
    private PortfolioService portfolioService;

    @GetMapping("/")
    public String index(Model model) {
        model.addAttribute("projects", portfolioService.getAllProjects());
        model.addAttribute("expertise", portfolioService.getAllExpertise());
        model.addAttribute("tools", portfolioService.getAllTools());
        return "index";
    }

    @GetMapping("/api/projects")
    @ResponseBody
    public List<Project> getProjects() {
        return portfolioService.getAllProjects();
    }

    @GetMapping("/api/expertise")
    @ResponseBody
    public List<Expertise> getExpertise() {
        return portfolioService.getAllExpertise();
    }

    @PostMapping("/api/contact")
    @ResponseBody
    public ContactMessage sendMessage(@RequestBody ContactMessage message) {
        return portfolioService.saveMessage(message);
    }

    @GetMapping("/about")
    public String about(Model model) {
        model.addAttribute("projects", portfolioService.getAllProjects());
        return "about";
    }

    @GetMapping("/projects")
    public String projects(Model model) {
        model.addAttribute("projects", portfolioService.getAllProjects());
        return "projects";
    }
}
