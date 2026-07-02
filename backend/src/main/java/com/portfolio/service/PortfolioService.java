package com.portfolio.service;

import com.portfolio.model.Project;
import com.portfolio.model.Expertise;
import com.portfolio.model.ContactMessage;
import com.portfolio.repository.ProjectRepository;
import com.portfolio.repository.ExpertiseRepository;
import com.portfolio.repository.ContactMessageRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class PortfolioService {

    @Autowired
    private ProjectRepository projectRepository;

    @Autowired
    private ExpertiseRepository expertiseRepository;

    @Autowired
    private ContactMessageRepository contactMessageRepository;

    public List<Project> getAllProjects() {
        return projectRepository.findAll();
    }

    public List<Expertise> getAllExpertise() {
        return expertiseRepository.findAll();
    }

    public ContactMessage saveMessage(ContactMessage message) {
        return contactMessageRepository.save(message);
    }

    public List<Project> getProjectsByType(String type) {
        return projectRepository.findByProjectType(type);
    }
}
