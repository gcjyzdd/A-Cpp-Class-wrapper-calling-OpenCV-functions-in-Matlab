%CLASS_INTERFACE Example MATLAB class wrapper to an underlying C++ class
classdef class_interface < handle
    properties (SetAccess = private, Hidden = true)
        objectHandle; % Handle to the underlying C++ class instance
    end
    methods
        %% Constructor - Create a new C++ class instance
        function this = class_interface(varargin)
            this.objectHandle = class_interface_mex('new', varargin{:});
        end
        
        %% Destructor - Destroy the C++ class instance
        function delete(this)
            class_interface_mex('delete', this.objectHandle);
        end
        
        %% Train - an example class method call
        function varargout = train(this, varargin)
            [varargout{1:nargout}] = class_interface_mex('train', this.objectHandle, varargin{:});
        end
        
        %% wait
        function varargout = wait(this, varargin)
            [varargout{1:nargout}] = class_interface_mex('wait', this.objectHandle, varargin{:});
        end
        
        %% wait
        function varargout = waitFlag(this, varargin)
            [varargout{1:nargout}] = class_interface_mex('waitFlag', this.objectHandle, varargin{:});
        end
        
        %% Init
        function varargout = init(this, varargin)
            [varargout{1:nargout}] = class_interface_mex('init', this.objectHandle, varargin{:});
        end
        
        %% SnedImg
        function varargout = sendImg(this, varargin)
            [varargout{1:nargout}] = class_interface_mex('sendImg', this.objectHandle, varargin{:});
        end
        
        %% Test - another example class method call
        function varargout = test(this, varargin)
            [varargout{1:nargout}] = class_interface_mex('test', this.objectHandle, varargin{:});
        end
    end
end