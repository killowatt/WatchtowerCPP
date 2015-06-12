
using System;
using OpenTK;

namespace WatchtowerClient.Graphics
{
    public class Camera
    {
        private Matrix4 _view;
        private Matrix4 _projection;
        //private Quaternion _quaternion;
        private bool _viewCalculated;
        private bool _projectionCalculated;
        private bool _rotationCalculated;

        private Vector3 _position;
        private Vector3 _rotation;
        private float _fieldOfView;
        private Vector2 _aspectRatio;

        public Matrix4 View
        {
            get
            {
                if (!_viewCalculated)
                {
                    Vector3 direction = new Vector3(
                        (float)(Math.Cos(_rotation.Z) * Math.Sin(_rotation.Y)),
                        (float)(Math.Sin(_rotation.Z)),
                        (float)(Math.Cos(_rotation.Z) * Math.Cos(_rotation.Y))
                        );

                    Vector3 right = new Vector3(
                        (float)(Math.Sin(_rotation.Y - 3.14f / 2.0f)),
                        0,
                        (float)(Math.Cos(_rotation.Y - 3.14f / 2.0f))
                        );

                    Vector3 up = Vector3.Cross(right, direction);

                    //up.Normalize();
                    //_quaternion = Quaternion.FromEulerAngles(_rotation * up);
                    //_view = Matrix4.CreateTranslation(_position) *
                    //        Matrix4.CreateFromQuaternion(_quaternion);
                    _view = Matrix4.LookAt(_position, _position + direction, up);
                }
                return _view;
            }
        }
        public Matrix4 Projection
        {
            get
            {
                if (!_projectionCalculated)
                {
                    _projection = Matrix4.CreatePerspectiveFieldOfView(_fieldOfView, _aspectRatio.X / _aspectRatio.Y,
                        0.5f, 1024);
                }
                return _projection;
            }
        }
        public Vector3 Position
        {
            get { return _position; }
            set 
            { 
                _position = value;
                _viewCalculated = false;
            }
        }
        public float X
        {
            get { return _position.X; }
            set
            {
                _position.X = value;
                _viewCalculated = false;
            }
        }
        public float Y
        {
            get { return _position.Y; }
            set
            {
                _position.Y = value;
                _viewCalculated = false;
            }
        }
        public float Z
        {
            get { return _position.Z; }
            set 
            { 
                _position.Z = value;
                _viewCalculated = false;
            }
        }
        public Vector3 Rotation
        {
            get { return _rotation; }
            set
            {
                Pitch = value.X;
                Yaw = value.Y;
                Roll = value.Z;
                _viewCalculated = false;
            }
        }
        public float Roll
        {
            get { return (float)(_rotation.X * (180 / Math.PI)); }
            set
            {
                _rotation.X = (float)(value * (Math.PI / 180));
                _viewCalculated = false;
                _rotationCalculated = false;
            }
        }
        public float Yaw
        {
            get { return (float)(_rotation.Y * (180 / Math.PI)); }
            set
            {
                _rotation.Y = (float)(value * (Math.PI / 180));
                _viewCalculated = false;
                _rotationCalculated = false;
            }
        }
        public float Pitch
        {
            get { return (float)(_rotation.Z * (180 / Math.PI)); }
            set
            {
                _rotation.Z = (float)(value * (Math.PI / 180));
                _viewCalculated = false;
                _rotationCalculated = false;
            }
        }
        public float FieldOfView
        {
            get { return (float)(_fieldOfView * (180 / Math.PI)); } // TODO: test to see if parenthesis is needed
            set
            {
                _fieldOfView = (float)(value * (Math.PI / 180));
                _projectionCalculated = false;
            }
        }
        public Vector2 AspectRatio
        {
            get { return _aspectRatio; }
            set
            {
                _aspectRatio = value;
                _projectionCalculated = false;
            }
        }

        public Camera()
        {
            Position = new Vector3(0);
            Rotation = new Vector3(0, 0, 0);
            FieldOfView = 90;
            AspectRatio = new Vector2(16, 9);
        }
    }
}
