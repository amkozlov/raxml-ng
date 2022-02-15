#!groovy

def BUILD_DIR_CLANG = "build-clang-10"
def BUILD_DIR_GCC = "build-gcc-11"

pipeline {

  agent {
    label 'docker-host || docker-jenkins'
  }

  options {
    timeout(time: 1, unit: 'HOURS')
  }

  stages {
    stage('Submodules') {
      agent {
        docker {
          reuseNode true
          image 'braintwister/ubuntu-20.04-clang-10:0.5'
        }
      }
      steps {
        sh '''
          git submodule update --init --recursive
          git submodule add https://github.com/amkozlov/ngtest.git
        '''
      }
    }
    stage('Build') {
      parallel {
        stage('clang-10') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-clang-10'
              dir 'docker'
            }
          }
          steps {
            sh '''
              rm -fr ${BUILD_DIR_CLANG} && mkdir -p ${BUILD_DIR_CLANG} && cd ${BUILD_DIR_CLANG}
              cmake -DCMAKE_BUILD_TYPE=Release .. 2>&1 |tee cmake.out
              make 2>&1 |tee make.out
            '''
          }
          post {
            always {
              recordIssues enabledForFailure: true, aggregatingResults: false,
                tool: clang(id: 'clang-10', pattern: '${BUILD_DIR_CLANG}/make.out')
            }
          }
        }
        stage('gcc-11') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-gcc-11'
              dir 'docker'
            }
          }
          steps {
            sh '''
              rm -fr ${BUILD_DIR_GCC} && mkdir -p ${BUILD_DIR_GCC} && cd ${BUILD_DIR_GCC}
              cmake -DCMAKE_BUILD_TYPE=Release .. 2>&1 |tee cmake.out
              make 2>&1 |tee make.out
            '''
          }
          post {
            always {
              recordIssues enabledForFailure: true, aggregatingResults: false,
                tool: clang(id: 'gcc-11', pattern: '${BUILD_DIR_GCC}/make.out')
            }
          }
        }
      }
    }
    stage('Unit tests') {
      parallel {
        stage('clang-10') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-clang-10'
              dir 'docker'
            }
          }
          steps {
            sh 'cd ${BUILD_DIR_CLANG} && make test'
          }
          post {
            always {
              step([
                $class: 'XUnitPublisher',
                thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
                tools: [[$class: 'GoogleTestType', pattern: '${BUILD_DIR_CLANG}/test/*.xml']]
              ])
            }
          }
        }
        stage('gcc-11') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-gcc-11'
              dir 'docker'
            }
          }
          steps {
            sh 'cd ${BUILD_DIR_GCC} && make test'
          }
          post {
            always {
              step([
                $class: 'XUnitPublisher',
                thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
                tools: [[$class: 'GoogleTestType', pattern: '${BUILD_DIR_GCC}/test/*.xml']]
              ])
            }
          }
        }
      }
    }
    stage('Regression tests') {
      parallel {
        stage('clang-10') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-clang-10'
              dir 'docker'
            }
          }
          steps {
            sh 'ngtest/runtest.py ${BUILD_DIR_CLANG}/bin/raxml-ng'
          }
        }
        stage('gcc-11') {
          agent {
            dockerfile {
              reuseNode true
              filename 'dockerfile-gcc-11'
              dir 'docker'
            }
          }
          steps {
            sh 'ngtest/runtest.py ${BUILD_DIR_GCC}/bin/raxml-ng'
          }
        }
      }
    }
  }
  post {
    success {
      mail to: 'bernd.doser@h-its.org', subject: "SUCCESS: ${currentBuild.fullDisplayName}", body: "All fine."
    }
    failure {
      mail to: 'bernd.doser@h-its.org', subject: "FAILURE: ${currentBuild.fullDisplayName}", body: "Failed."
    }
  }
}
